#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

    #include <bits/stdc++.h>
    #include <pthread.h>
    #include <mpi.h>

    #define TRACKER_RANK 0

    //* abstract form of a file in C style
    typedef struct {
        int seg_num;
        std::string name;
        std::vector<std::string> segments;
    } File;

    //* abstract form of a client in C style
    typedef struct {
        int files_num;
        int needed_num;
        std::vector<File> files;
        std::vector<std::string> files_needed;
    } Client;

    //* abstract form of a seeder in C style
    typedef struct {
        int id;
        bool is_seeding;
    } Seeder;

    //* abstract form of a seeders without class or template
    typedef std::map<std::string, std::vector<Seeder>> Seeds;

    void check(bool condition, std::string err_msg, std::string func_name);
    void print_client(Client client);
    void print_client_tracker(Client client);
    std::string serialize_client(Client client);
    void deserialize_client(Client &client, std::string data);
    void ask_tracker_master(Client client, int rank);
    void read_client_file(std::string file_path, Client &client);

#endif