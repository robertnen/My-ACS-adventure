#include "client.hpp"

//* used only to prevent std::vector dynamic reallocation racing conditions
pthread_mutex_t mutex;

void get_seeds(std::vector<Seeder>& seeds, int &size, int &seeds_num, File &file) {
    size = file.name.length();  //* size is modified before and needs to be updated

    //* send size and name of needed file
    MPI_Send(&size, 1, MPI_INT, TRACKER_RANK, 0, MPI_COMM_WORLD);
    MPI_Send(file.name.data(), file.name.length(), MPI_CHAR, TRACKER_RANK, 1, MPI_COMM_WORLD);

    //* get seeders for the file
    MPI_Recv(&size, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::string data(size, ' ');
    MPI_Recv(&data[0], size, MPI_CHAR, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //* serialize it in this format seg-num_id1_id2_id3_...
    std::istringstream iss(data);

    iss >> file.seg_num >> seeds_num;

    for (int j = 0; j < seeds_num; j++) {
        Seeder s;

        iss >> s.id;
        seeds.push_back(s);
    }
}

void *download_thread_func(void *arg) {
    std::pair<int, Client*> down_args = *(std::pair<int, Client*>*) arg;

    //* resolve the args
    int rank = down_args.first;
    Client* client = down_args.second;

    //* send initial data and ask if it can seed
    //! same thing here as at line 203, read there
    ask_tracker_master(*client, rank);

    for (int i = 0; i < client->needed_num; i++) {
        File file;
        file.name = (*client).files_needed[i];
        int size = file.name.length(), seeds_num;

        std::vector<Seeder> seeds;
        get_seeds(seeds, size, seeds_num, file);

        int id;

        //* read segments now
        for (int j = 0; j < file.seg_num; j++) {
            if (j % 10 == 0) {
                get_seeds(seeds, size, seeds_num, file);
                id = rand() % seeds.size();
                id = seeds[id].id;
            }

            std::ostringstream oss;
            std::string data;

            oss << file.name << " " << j;

            data = oss.str();
            size = data.length();

            //* send size and name of needed file
            MPI_Send(&size, 1, MPI_INT, id, 3, MPI_COMM_WORLD);
            MPI_Send(data.data(), size, MPI_CHAR, id, 4, MPI_COMM_WORLD);

            //* get seeders for the file
            MPI_Recv(&size, 1, MPI_INT, id, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::string ans(size, ' ');
            MPI_Recv(&ans[0], size, MPI_CHAR, id, 6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (ans == "ACK") {
                //* get segment for the file
                MPI_Recv(&size, 1, MPI_INT, id, 7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                std::string msg(size, ' ');
                MPI_Recv(&msg[0], size, MPI_CHAR, id, 8, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                file.segments.push_back(msg);
            } else {  //* the seeder doesn't have the segment
                std::clog << "Rank " << rank << " received NACK for a segment!\n";
                j--;
                if (seeds.size() < 1) get_seeds(seeds, size, seeds_num, file);
                id = rand() % seeds.size();
                id = seeds[id].id;
                continue;
            }
        }

        //? prevent the weirdest race condition of std::vector
        //? when too many updates are happening it changes the addresses
        //? of many iterators for a single push_back...
        pthread_mutex_lock(&mutex);
        client->files.push_back(file);
        client->files_num++;
        pthread_mutex_unlock(&mutex);

        //* tell the tracker the file is downloaded
        int ssize = 3;
        MPI_Send(&ssize, 1, MPI_INT, TRACKER_RANK, 0, MPI_COMM_WORLD);
        MPI_Send("FND", 3, MPI_CHAR, TRACKER_RANK, 1, MPI_COMM_WORLD);

        ssize = file.name.length();

        MPI_Send(&ssize, 1, MPI_INT, TRACKER_RANK, 20, MPI_COMM_WORLD);
        MPI_Send(file.name.data(), ssize, MPI_CHAR, TRACKER_RANK, 21, MPI_COMM_WORLD);

        //* write the downloaded file
        std::string file_path = "client" + std::to_string(rank) + "_" + file.name;
        std::ofstream fout(file_path.c_str());

        for (std::string segment_file : file.segments) fout << segment_file + "\n";

        fout.close();
    }

    //? prevent the weirdest race condition of std::vector
    //? when too many updates are happening it changes the addresses
    //? of many iterators for a single push_back...
    pthread_mutex_lock(&mutex);
    client->needed_num = 0;
    client->files_needed.clear();
    pthread_mutex_unlock(&mutex);

    std::clog << "Rank " << rank << " finished downloading!\n";

    //* tells the tracker the peer finished downloading
    int size = 3;
    MPI_Send(&size, 1, MPI_INT, TRACKER_RANK, 0, MPI_COMM_WORLD);
    MPI_Send("END", 3, MPI_CHAR, TRACKER_RANK, 1, MPI_COMM_WORLD);

    return NULL;
}

void *upload_thread_func(void *arg) {
    std::pair<int, Client*> down_args = *(std::pair<int, Client*>*) arg;

    //* resolve args and get info
    int rank = down_args.first, seg;
    Client* client = down_args.second;

    while (true) {
        int size;
        MPI_Status status;

        //* wait for any request
        MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
        std::string msg(size, ' ');
        MPI_Recv(&msg[0], size, MPI_CHAR, status.MPI_SOURCE, 4, MPI_COMM_WORLD, &status);

        if (msg == "END") {
            std::clog << "Rank " << rank << " finished uploading!\n";
            break;
        }

        //* deserialize the format name_segment-position
        std::istringstream iss(msg);
        File file;

        iss >> file.name >> seg;

        file.seg_num = -1;  //? assume the file is in the seeder's content

        //* find the file by name (mutex because of the std::vector dynamic implementation)
        pthread_mutex_lock(&mutex);
        for (File f : (*client).files)
            if (f.name == file.name) {
                file = f;
                break;
            }
        pthread_mutex_unlock(&mutex);

        if (file.seg_num == -1) {  //* file / segment not found
            //! the client doesn't have / find the hash or it is not yet downloaded
            size = 3;
            MPI_Send(&size, 1, MPI_INT, status.MPI_SOURCE, 5, MPI_COMM_WORLD);
            MPI_Send("NCK", 3, MPI_CHAR, status.MPI_SOURCE, 6, MPI_COMM_WORLD);
        } else {  //* segment exists
            //! send ACK
            size = 3;
            MPI_Send(&size, 1, MPI_INT, status.MPI_SOURCE, 5, MPI_COMM_WORLD);
            MPI_Send("ACK", size, MPI_CHAR, status.MPI_SOURCE, 6, MPI_COMM_WORLD);

            //! send the segment asked
            size = file.segments[seg].length();
            MPI_Send(&size, 1, MPI_INT, status.MPI_SOURCE, 7, MPI_COMM_WORLD);
            MPI_Send(file.segments[seg].data(), size, MPI_CHAR, status.MPI_SOURCE, 8, MPI_COMM_WORLD);
        }
    }

    return NULL;
}

void tracker(int numtasks, int rank) {
    Seeds seeds;
    std::vector<Client> clients;

    //* get initial data about clients
    //! the tracker only at the start knows everything about the clients
    //! because this is asked in the homework. After the tracker only updates
    //! it's info about the client's files owned and needed, not about segments,
    //! neither it checks if a client contains a specific hash
    for (int i = 1; i < numtasks; i++) {
        int size;
        MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::string data(size, ' ');
        MPI_Recv(&data[0], size, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        Client client;

        //* data is in a string format like size_data1_data2_...
        deserialize_client(client, data);
        clients.push_back(client);

        for (File file : client.files) {
            Seeder seeder;

            seeder.id = i;
            seeder.is_seeding = false;

            //* remembers where the files can be found
            //! it doesn't need mutex yet because there is an ACK forward needed
            seeds[file.name].push_back(seeder);
        }

        //? something went wrong, tracker not working as intented
        if (size <= 0) MPI_Send("NOT", 3, MPI_CHAR, i, 3, MPI_COMM_WORLD);

        //* send ack to peer
        MPI_Send("ACK", 3, MPI_CHAR, i, 9, MPI_COMM_WORLD);
    }

    //* checks if a peer finished downloading
    std::vector<bool> is_done(numtasks + 1, false);
    bool is_working = true;

    //* work while peers are downloading and / or uploading
    while (is_working) {
        is_working = false;  //? assume it is done

        for (int i = 1; i < numtasks; i++) {
            if (is_done[i]) continue;
            is_working = true;  //? peer downloading found
            int size;

            //* receive needed file or command
            MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::string name(size, ' ');
            MPI_Recv(&name[0], size, MPI_CHAR, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //* check if peer finished downloading
            if (name == "END") {
                is_done[i] = true;
                continue;
            }

            //* check if peer finished downloading a file
            if (name == "FND") {
                //* receive name of the downloaded file
                MPI_Recv(&size, 1, MPI_INT, i, 20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                std::string file_name(size, ' ');
                MPI_Recv(&file_name[0], size, MPI_CHAR, i, 21, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                //* update seeders info
                Seeder seeder;

                seeder.id = i;
                seeder.is_seeding = true;

                //? prevent the weirdest race condition of std::vector
                //? when too many updates are happening it changes the addresses
                //? of many iterators for a single push_back...
                pthread_mutex_lock(&mutex);
                seeds[file_name].push_back(seeder);
                pthread_mutex_unlock(&mutex);

                std::clog << "Peer " << i << " downloaded " + file_name + "\n";
                continue;
            }

            //* peer wants to update it's own seeders info, send him that
            std::vector<Seeder> s = seeds[name];
            std::ostringstream oss;
            std::string to_send;

            //* find number of segments
            for (File file : clients[s[0].id - 1].files) {
                if (file.name == name) {
                    size = file.seg_num;
                    break;
                }
            }

            //? send serialized like this segments-number_seeder1_seeder2_seeder3_...
            oss << size << " " << s.size();

            for (auto t : s) oss << " " << t.id;

            to_send = oss.str();
            size = to_send.length();

            //* send number of segments and list of seeders
            MPI_Send(&size, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
            MPI_Send(to_send.data(), size, MPI_CHAR, i, 11, MPI_COMM_WORLD);
        }
    }

    //* everyone finished downloading, tell them to stop seeding
    for (int i = 1; i < numtasks; i++) {
        int size = 3;
        MPI_Send(&size, 1, MPI_INT, i, 3, MPI_COMM_WORLD);
        MPI_Send("END", 3, MPI_CHAR, i, 4, MPI_COMM_WORLD);
    }
}

void peer(int numtasks, int rank) {
    pthread_t download_thread;
    pthread_t upload_thread;
    void *status;
    int r;

    Client client;
    std::string file_path = "in";

    //* init the peers
    file_path += std::to_string(rank) + ".txt";
    read_client_file(file_path, client);

    std::pair<int, Client*> down_args = {rank, &client};

    r = pthread_create(&download_thread, NULL, download_thread_func, (void *) &down_args);
    check(r, "Eroare la crearea thread-ului de download", "main");

    r = pthread_create(&upload_thread, NULL, upload_thread_func, (void *) &down_args);
    check(r, "Eroare la crearea thread-ului de upload", "main");

    r = pthread_join(download_thread, &status);
    check(r, "Eroare la asteptarea thread-ului de download", "main");

    r = pthread_join(upload_thread, &status);
    check(r, "Eroare la asteptarea thread-ului de upload", "main");
}

int main (int argc, char *argv[]) {
    int numtasks, rank, provided;

    //* check is a function that detects if the program works as intended or it needs to stop
    check(pthread_mutex_init(&mutex, NULL), "Mutex not created", "main");

    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    check(provided < MPI_THREAD_MULTIPLE, "MPI nu are suport pentru multi-threading", "main");

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    rank == TRACKER_RANK ? tracker(numtasks, rank) : peer(numtasks, rank);

    MPI_Finalize();
    check(pthread_mutex_destroy(&mutex), "Mutex not destroyed", "main");

    if (!rank) std::clog << "Thanks for using BitTorrent!\n";
}
