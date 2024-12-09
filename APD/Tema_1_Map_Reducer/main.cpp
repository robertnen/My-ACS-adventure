#include "custom_func.hpp"

void* threads_func(void *arg) {
    std::pair<Data*, int> t = *(std::pair<Data*, int>*) arg;
    Data* data = t.first;
    int id = t.second;

    //? thread is a mapper
    if (isMapper(data, id)) mapper(data, id);

    pthread_barrier_wait(data->barrier);

    //? thread is a reader
    if (isReducer(data, id)) reducer(data, id);

    pthread_barrier_wait(data->barrier);

    //* first reducer thread gives the output
    if (id == data->mappers_num) output(data, id);

    pthread_exit(NULL);
}


int main(int argc, char **argv) {
    check(argc == 4, "Try ./tema1 <num_mappers> <num_reducers> <input_file>.",
        "main", ON_ERROR_EXIT);

    MapReduce MapRed(atoi(argv[1]), atoi(argv[2]), argv[3]);

    //* check if the input is wrong or if file is missing
    checkArguments(MapRed);

    //* read the tasks
    std::ifstream fin(MapRed.getPath());
    std::vector<std::string> paths;
    std::string line;
    Data data;
    int n = -1;

    std::getline(fin, line, '\n');

    n = atoi(line.c_str());  //! get the number of files

    check(n > 0, "No files to read.", "main", ON_ERROR_EXIT);

    //* read input file
    for (int i = 0; i < n; i++) {
        std::getline(fin, line, '\n');

        check(checkPath(line), "File doesn't exist.",
            "main", ON_ERROR_EXIT);

        paths.push_back(line);
    }

    //* get information from files
    for (std::string path : paths)
        data.files.push_back(File{.path = path, .isAlive = true});

    data.file_num = (int) data.files.size();
    check(n == data.file_num, "Number of files read is different.",
        "main", ON_ERROR_EXIT);

    //* declar threads essentials
    void *status;
    pthread_t threads[MapRed.getThreadsNum()];
    std::vector<std::pair<Data*, int>> thread_data;

    data.barrier = (pthread_barrier_t *) malloc(sizeof(pthread_barrier_t));
    data.mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));

    check(data.barrier != NULL, "Barrier not allocated.", "main", ON_ERROR_EXIT);
    check(data.mutex != NULL, "Mutex not allocated.", "main", ON_ERROR_EXIT);

    //* verify threads essentials
    check(!pthread_barrier_init(data.barrier, NULL, MapRed.getThreadsNum()),
            "Barrier not created.", "main", ON_ERROR_EXIT);

    check(!pthread_mutex_init(data.mutex, 0), "Mutex not created.",
            "main", ON_ERROR_EXIT);

    //* because std::vector reallocates dynamically, I need this
    //* so the variable doesn't change it's address
    thread_data.reserve(MapRed.getThreadsNum());
    data.mappers.reserve(MapRed.getMappers());
    data.reducers.reserve(MapRed.getThreadsNum());

    //* add empty slots
    data.mappers.resize(MapRed.getMappers());
    data.reducers.resize(MapRed.getThreadsNum());

    //* get other data
    data.mappers_num = MapRed.getMappers();
    data.reducers_num = MapRed.getReducers();

    //* create threads
    for (int i = 0; i < MapRed.getThreadsNum(); i++) {
        thread_data.push_back({&data, i});

        check(!pthread_create(&threads[i], NULL, threads_func, (void *) &thread_data[i]),
                "Thread couldn't be created.", "main", ON_ERROR_EXIT);
    }

    // * join threads
    for (int i = 0; i < MapRed.getThreadsNum(); i++) {
        check(!pthread_join(threads[i], &status), "Failed to join threads.",
                "main", ON_ERROR_EXIT);
    }

    //* destroy manually allocated space
    check(!pthread_barrier_destroy(data.barrier),
            "Barrier not destroyed.", "main", ON_ERROR_CONTINUE);

    check(!pthread_mutex_destroy(data.mutex), "Mutex not destroyed.",
            "main", ON_ERROR_CONTINUE);

    //* free allocated memory with malloc
    free(data.barrier);
    free(data.mutex);

    return 0;
}
