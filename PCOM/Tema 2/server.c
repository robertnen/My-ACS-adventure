#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define DEBUG 0

typedef struct sockaddr_in s_in;
typedef struct sockaddr s_ad;
typedef struct pollfd poll_fd;

typedef struct {
    int len;
    s_in client_addr;
    char topic[51], msg[1500];
} Message;

typedef struct {
    bool is_on;
    int num_mess, fd;
    char id[15];
} Subscriber;

typedef struct {
    int clients_num, replies_num;
    Subscriber clients[100];
    Message replies[100];
    char topic[51];
} Post;

typedef struct {
    Post posts[150];
    int posts_num;
} Forum;

//! global variables
bool to_update;
Forum moodle;  //* nume foarte creativ :D
Subscriber *clients;
int clients_num, s_fd_udp, s_fd_tcp;
s_in server = (s_in) {0}, client = (s_in) {0};

//! constants
const int EXIT_SIZE = 5;
const char EXIT[] = "exit\n";

//? used when send_error returns true
void fail_error(char *err_msg) {
    fprintf(stderr, "Invalid send_error: %s.\n", err_msg);
    exit(1);
}

//? used when send_error returns true
void fail_err(char* err_msg) {
    fprintf(stderr, "%s.\n", err_msg);
    exit(1);
}

//? sends errors for wrong commands (1 - exit failed)
bool send_error(char* err_msg, char* example_cmd) {
    //* <error_msg>. Command example: <example_cmd>

    if (!strlen(err_msg)) {
        fprintf(stderr, "err_msg in send_error is empty");
        return 1;
    }

    if (!strlen(example_cmd)) {
        fprintf(stderr, "example_cmd in send_error is empty");
        return 1;
    }

    fprintf(stderr, "%s. Command example: %s\n", err_msg, example_cmd);
    exit(1);
}

//? used to test if the command ./server is used as it should be
void test_args(int argc) {
    if (argc < 2)  //* less than 2 arguments
        if (send_error("Not enough arguments", "./server <port>"))
            fail_error("if argc < 2");

    if (argc > 2)  //* more than 2 arguments
        if (send_error("Too many arguments", "./server <port>"))
            fail_error("if argc > 2");
}

//? transforms a string to a number
int char_to_num(const char* str) {
	long ans = 0;
    int len = strlen(str), i = 0;
    bool flag = false;

    while (i < len && str[i] == ' ') i++;

    if (i < len && str[i] == '-') {flag = true; i++;}
    if (i < len && i && str[i] == '+' && str[i - 1] == '-')
        if (send_error("Invalid port (not int)", "./server <port>"))
            fail_error("+ - with no reason");

    if (i < len && str[i] == '+') i++;

    while (i < len && ('0' <= str[i] && str[i] <= '9')) {
        ans = ans * 10 + str[i] - '0';

        if (ans > INT_MAX && flag) return INT_MIN;
        else if (ans > INT_MAX) return INT_MAX;

        i++;
    }

    return flag ? -ans : ans;
}

//? used to remove all remaining clients on exit
void remove_tcp_clients() {
    bool flag;

    for (int i = 0; i < clients_num; i++) {
        if (!clients[i].is_on) continue;  //* client not online

        flag = send(clients[i].fd, &EXIT_SIZE, 4, 0) < 0;
        if (flag) fail_err("Failed to send size");

        flag = send(clients[i].fd, EXIT, EXIT_SIZE, 0) < 0;
        if (flag) fail_err("Failed to send exit command");

        close(clients[i].fd);
    }
}

//* searches if a client already exists
int find_id(char* id) {
    for (int i = 0; i < clients_num; i++)
        if (!strcmp(clients[i].id, id))
            return i;

    return -1;
}

//* searches if a client already exists
int find_fd(int fd) {
    for (int i = 0; i < clients_num; i++)
        if (clients[i].fd == fd)
            return i;

    return -1;
}

//* client gets connected to the server
int accept_subscribe(socklen_t size) {
    char id[15];
    int fd, bytes_received;

    fd = accept(s_fd_tcp, (s_ad *) &client, &size);
    if (fd < 0) return -5;

    //* disable Nagle algorithm
    const bool disable_flag = true;
    int ret = setsockopt(s_fd_tcp, IPPROTO_TCP, TCP_NODELAY,
                         (char *) &disable_flag, sizeof(int));

    if (ret) fail_err("Failed to stop the Nagle algorithm");

    bytes_received = recv(fd, id, 15, 0);
    if (bytes_received < 0) fail_err("Server failed to receive");

    id[bytes_received] = '\0';

    int pos = find_id(id);

    if (DEBUG)
        printf("Trying to connect: pos = %d\n", pos);

    bool flag;

    if (pos != -1) {
        flag = true;

        if (send(fd, &flag, sizeof(bool), 0) < 0)
            fail_err("Failed to send same flag.\n");

        close(fd);

        printf("Client %s already connected.\n", id);

        return -4;
    }

    flag = false;

    if (send(fd, &flag, sizeof(bool), 0) < 0)
        fail_err("Failed to send flag.\n");

    printf("New client %s connected from %s:%i.\n",
            id, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    strcpy(clients[clients_num].id, id);
    clients[clients_num++].fd = fd;

    //TODO add topics

    if (DEBUG)
        printf("Client added.\n");

    return fd;
}

//* client gets subscribed to a post / reply
void subscribe(int fd, char* sub) {
    if (!sub) return;  //* failed to sub (not enough args)

    sub = strtok(NULL, " ");

    if (!sub) return;  //* failed to sub (not enough args)

    char id[15];

    int pos = find_fd(fd);

    if (pos != -1) strcpy(id, clients[pos].id);
    else return;

    //* maybe there is a topic already
    for (int i = 0; i < moodle.posts_num; i++)
        if (!strcmp(moodle.posts[i].topic, sub)) {
            for (int j = 0; j < moodle.posts[i].clients_num; j++)  //* update fd if exists
                if (!strcmp(moodle.posts[i].clients[j].id, id)) {
                    moodle.posts[i].clients[j].fd = fd;
                    return;
                }

            moodle.posts[i].clients[moodle.posts[i].clients_num].fd = fd;
            moodle.posts[i].clients[moodle.posts[i].clients_num].is_on = true;

            strcpy(moodle.posts[i].clients[moodle.posts[i].clients_num].id, id);

            moodle.posts[i].clients[moodle.posts[i].clients_num++].num_mess = moodle.posts[i].replies_num;
            return;
        }

    //* topic doesn't exist yet
    moodle.posts[moodle.posts_num].clients_num = 1;
    moodle.posts[moodle.posts_num].clients[0].fd = fd;
    moodle.posts[moodle.posts_num].clients[0].is_on = true;

    strcpy(moodle.posts[moodle.posts_num].topic, sub);
    strcpy(moodle.posts[moodle.posts_num].clients[0].id, id);
}

//* client gets unsubscribed from a post / reply
void unsubscribe(int fd, char* unsub) {
    if (!unsub) return;  //* failed to unsub (not enough args)

    unsub = strtok(NULL, " ");

    if (!unsub) return;  //* failed to unsub (not enough args)

    for (int i = 0; i < moodle.posts_num; i++)
        if (!strcmp(moodle.posts[i].topic, unsub))  //* topic found
            for (int j = 0; j < moodle.posts[i].clients_num; j++)
                if (moodle.posts[i].clients[j].fd == fd) {
                    for (int k = j; k < moodle.posts[i].clients_num; k++)  //* removing client
                        moodle.posts[i].clients[k] = moodle.posts[i].clients[k + 1];

                    moodle.posts[i].clients_num--;
                    return;
                }
}

//* sync the clients with the server so moodle works
void update_forum() {
    if (!to_update) return;

    int size = sizeof(int) + sizeof(s_ad) + 51;
    Message msg;

    for (int i = 0; i < moodle.posts_num; i++)
        for (int j = 0; j < moodle.posts[i].clients_num; j++)
            if (moodle.posts[i].clients[j].is_on)
                if (moodle.posts[i].replies_num > moodle.posts[i].clients[j].num_mess)
                    for (int k = moodle.posts[i].clients[j].num_mess; k < moodle.posts[i].replies_num; k++) {
                        msg = moodle.posts[i].replies[k];

                        size += msg.len;  //* actual size -> size + msg.size

                        if (send(moodle.posts[i].clients[j].fd, &size, sizeof(int), 0))
                            fail_err("Server can't send size of message to client");

                        if (send(moodle.posts[i].clients[j].fd, &msg, size, 0) < 0)
                            fail_err("Server can't send message to client");

                        size -= msg.len;  //* default value (empty message)
                        moodle.posts[i].clients[j].num_mess = moodle.posts[i].replies_num;
                    }
}

int main(int argc, char **argv) {
    if (setvbuf(stdout, NULL, _IONBF, BUFSIZ) < 0) fail_err("stvbuf > 0");

    int port, fds = 3, bytes_received;
    socklen_t len;
    Message msg;

    test_args(argc);

    clients = (Subscriber *) calloc(1000, sizeof(Subscriber));
    port = char_to_num(argv[1]);

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //* bind udp
    s_fd_udp = socket(AF_INET, SOCK_DGRAM, 0);

    if (s_fd_udp < 0) fail_err("Failed to create UDP socket");

    if (bind(s_fd_udp, (struct sockaddr *) &server, sizeof(s_in)) < 0)
        fail_err("Failed to bind UDP socket");

    //* bind tcp
    s_fd_tcp = socket(AF_INET, SOCK_STREAM, 0);

    if (s_fd_tcp < 0) fail_err("Failed to create TCP socket");

    if (bind(s_fd_tcp, (struct sockaddr *) &server, sizeof(s_in)) < 0)
        fail_err("Failed to bind UDP socket");

    //* disable Nagle algorithm
    const bool disable_flag = true;
    int ret = setsockopt(s_fd_tcp, IPPROTO_TCP, TCP_NODELAY,
                         (char *) &disable_flag, sizeof(int));

    if (ret) fail_err("Failed to stop the Nagle algorithm");

    if (listen(s_fd_tcp, 50))
        fail_err("Failed to listen on socket");

    poll_fd p_fds[1000];

    p_fds[0] = (poll_fd) {.fd = STDIN_FILENO, .events = POLLIN};
    p_fds[1] = (poll_fd) {.fd = s_fd_udp, .events = POLLIN};
    p_fds[2] = (poll_fd) {.fd = s_fd_tcp, .events = POLLIN};

    if (DEBUG)
        printf("Starting the server...\n");

    while (true) {
        char cmd[150], inp_udp[2500];
        short flags[3];  //* used for stdin, udp and tcp

        poll(p_fds, fds, -1);

        flags[0] = p_fds[0].revents & POLLIN;  //* stdin
        flags[1] = p_fds[1].revents & POLLIN;  //* s_udp
        flags[2] = p_fds[2].revents & POLLIN;  //* s_tcp

        if (flags[0]) {  //* stdin - pentru exit
            if (fgets(cmd, 120, stdin) && !strcmp(cmd, EXIT)) {
                remove_tcp_clients();

                close(s_fd_udp);
                close(s_fd_tcp);

                break;
            }
        } else if (flags[1]) {  //* s_udp
            len = sizeof(client);

            bytes_received = recvfrom(s_fd_udp, inp_udp, 2000,
                                        MSG_WAITALL, (s_ad *) &client, &len);

            if (bytes_received != -1) {
                inp_udp[bytes_received] = '\n';

                msg = (Message) {0};  //? creating a new message

                msg.len = bytes_received;
                msg.client_addr = client;

                strcpy(msg.topic, inp_udp);
                strcpy(inp_udp, inp_udp + 50);
                strcpy(msg.msg, inp_udp);

                bool is_new = false;  //? checking if it is a post or a reply

                for (int i = 0; i < moodle.posts_num; i++)
                    if (!strcmp(moodle.posts[i].topic, msg.topic)) {
                        moodle.posts[i].replies[moodle.posts[i].replies_num++] = msg;
                        is_new = true;
                        break;
                    }

                if (!is_new) {
                    strcpy(moodle.posts[moodle.posts_num].topic, msg.topic);
                    moodle.posts[moodle.posts_num].replies[moodle.posts[moodle.posts_num].replies_num] = msg;

                    moodle.posts[moodle.posts_num].replies_num++;
                    moodle.posts_num++;
                }
            }
        } else if (flags[2]) {  //* s_tcp
            int new_fd = accept_subscribe(sizeof(s_ad));

            if (new_fd > -1) {
                p_fds[fds].fd = new_fd;
                p_fds[fds++].events = POLLIN;
            }
        } else {
            for (int i = 3; i < fds; i++) {
                if (p_fds[i].revents & POLLIN) {
                    int bytes_read = recv(p_fds[i].fd, cmd, 150, 0);

                    if (!bytes_read) {  //* client disconnected
                        int pos = find_fd(p_fds[i].fd);

                        if (pos != -1) {
                            printf("Client %s disconnected.\n", clients[pos].id);

                            for (int j = pos; j < clients_num - 1; j++)
                                clients[j] = clients[j + 1];

                            clients_num--;
                        }

                        for (int j = i; j < fds; j++) p_fds[j] = p_fds[j + 1];

                        fds--;
                        break;
                    }

                    cmd[bytes_read] = '\n';
                    char *p = strtok(cmd, " ");

                    if (!strcmp(p, "subscribe")) subscribe(p_fds[i].fd, p);
                    if (!strcmp(p, "unsubscribe")) unsubscribe(p_fds[i].fd, p);
                }
            }
        }
        update_forum();
    }

    if (DEBUG) {
        printf("Server is closing...\n");
        printf("Number of clients: %d\n", clients_num);
    }

    free(clients);

    return 0;
}
