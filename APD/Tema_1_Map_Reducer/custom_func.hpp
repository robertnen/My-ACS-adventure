#ifndef __CUSTOM_FUNC_H__
#define __CUSTOM_FUNC_H__

    #include <bits/stdc++.h>
    #include <pthread.h>
    #include <unistd.h>

    const bool ON_ERROR_EXIT = true;
    const bool ON_ERROR_CONTINUE = false;

    typedef std::pair<std::string, std::set<int>> word;

    typedef struct _ {
        std::map<std::string, std::set<int>> words;
    } Words;

    typedef struct __ {
        std::string path;
        bool isAlive;
    } File;

    typedef struct ___ {
        std::vector<File> files;  //* everything about the files
        std::vector<Words> mappers;
        std::vector<Words> reducers;
        pthread_barrier_t *barrier;
        pthread_mutex_t *mutex;
        int file_num = 0;
        int mappers_num = 0;
        int reducers_num = 0;
    } Data;

    class MapReduce {
    public:
        MapReduce(int mappers, int reducers, std::string path)
            : mappers(mappers), reducers(reducers), path(path) {}

        int getMappers() { return mappers; }
        int getReducers() { return reducers; }
        std::string getPath() { return path; }
        int getThreadsNum() { return mappers + reducers; }

        bool checkMap() { return mappers > 0; }
        bool checkReducers() { return reducers > 0; }
        bool checkPath() { return ( access( path.c_str(), F_OK ) != -1 ); }
    private:
        int mappers = 0, reducers = 0;
        std::string path;
    };


    void check(bool condition, std::string message, std::string name_func, const bool forceExit);
    void checkArguments(MapReduce MapRed);

    inline bool checkPath(std::string path) { return ( access( path.c_str(), F_OK ) != -1 ); }
    inline bool isMapper(Data *data, int id) { return (0 <= id && id < data->mappers_num); }
    inline bool isReducer(Data *data, int id) { return (data->mappers_num <= id && id < data->mappers_num + data->reducers_num); };

    void process_file(Data *data, int id, File file, int file_id);
    void mapper(Data *data, int id);
    void reducer(Data *data, int id);
    void output(Data *data, int id);

#endif