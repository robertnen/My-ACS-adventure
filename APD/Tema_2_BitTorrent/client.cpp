#include "client.hpp"

//* checks if the program works as intended, else it aborts it
void check(bool condition, std::string err_msg, std::string func_name) {
    if (!condition) return;  //* there is no error

    //* give error and close
    std::cerr << "The following function gave the error: " << err_msg << ".\n"
              << "Closing the program to prevent from data corruption...\n";

    //! something really bad happen with the program, abort it
    exit(-1);
}

//* log everything about a client
void print_client(Client client) {
    std::cout << "Owned: " << client.files_num << "\n{";
    for (File file : client.files) std::cout << file.name << ": " << file.seg_num << " | ";
    std::cout << "}\n";

    std::cout << "Needed: " << client.needed_num << "\n{";
    if (client.needed_num)
        for (std::string name : client.files_needed) std::cout << name << " ";
    std::cout << "}\n";
}

//* log info known by tacker about clients
void print_client_tracker(Client client) {
    std::cout << "Owned: " << client.files_num << "\n{";
    for (File file : client.files) std::cout << file.name << " ";
    std::cout << "}\n";

    std::cout << "Needed: " << client.needed_num << "\n{";
    for (std::string name : client.files_needed) std::cout << name << " ";
    std::cout << "}\n";
}

//* prepare info to be send in the format files-num_name1_seg-num1_name2_seg-num2...
std::string serialize_client(Client client) {
    std::ostringstream oss;

    oss << client.files_num << " ";

    for (File file : client.files) {
        oss << file.name << " " << file.seg_num << " ";

        for (std::string segment : file.segments)
            oss << segment << " ";
    }

    oss << client.needed_num << " ";

    for (std::string name : client.files_needed)
        oss << name << " ";

    return oss.str();
}

//* read info received in the format files-num_name1_seg-num1_name2_seg-num2...
void deserialize_client(Client &client, std::string data) {
    std::istringstream iss(data);
    std::string name;

    iss >> client.files_num;

    for (int i = 0; i < client.files_num; i++) {
        File file;
        iss >> file.name >> file.seg_num;

        for (int j = 0; j < file.seg_num; j++) {
            iss >> name;
            file.segments.push_back(name);
        }

        client.files.push_back(file);
    }

    iss >> client.needed_num;

    for (int i = 0; i < client.needed_num; i++) {
        iss >> name;
        client.files_needed.push_back(name);
    }
}

//* more info in 'tema2.cpp', but it sends the initial data about clients to tracker
void ask_tracker_master(Client client, int rank) {
    std::string serialized_data = serialize_client(client);
    int size = serialized_data.length();

    //* send everything about the client to tracker
    MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(serialized_data.data(), size, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

    //* wait for answer like a good guy
    char answer[5];
    MPI_Recv(answer, 3, MPI_CHAR, TRACKER_RANK, 9, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    if (answer[0] != 'A' || answer[1] != 'C' || answer[2] != 'K')
        check(false, "ACK not sent from tracker", "ask_tracker_master");

    //* show that peer got ack from tracker
    std::clog << "Client " << rank << " got ACK from tracker.\n";
}

//* read for each client what he has and what he needs
void read_client_file(std::string file_path, Client &client) {
    std::ifstream fin(file_path.c_str());
    std::string line;

    //* check if file exists, it can be opened and read
    check(!fin.is_open(), "File at " + file_path + " couldn't be opened", "read_client_file");

    fin >> client.files_num;

    for (int i = 0; i < client.files_num; i++) {
        File file;

        fin >> file.name >> file.seg_num;

        for (int j = 0; j < file.seg_num; j++) {
            fin >> line;
            file.segments.push_back(line);
        }

        client.files.push_back(file);
    }

    fin >> client.needed_num;

    for (int i = 0; i < client.needed_num; i++) {
        fin >> line;

        client.files_needed.push_back(line);
    }

    fin.close();
}