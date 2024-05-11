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
    if (argc < 4)  //* less than 4 arguments
        if (send_error("Not enough arguments", "./subscriber <id> <ip> <port>"))
            fail_error("if argc < 4");

    if (argc > 4)  //* more than 4 arguments
        if (send_error("Too many arguments", "./subscriber <id> <ip> <port>"))
            fail_error("if argc > 4");
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

int main(int argc, char **argv) {
    if (setvbuf(stdout, NULL, _IONBF, BUFSIZ) < 0) fail_err("stvbuf > 0");

    test_args(argc);

    int port, s_fd, fds, bytes_received, msg_size;
    unsigned int type;

    s_in server = (s_in) {0};
    char msg[3500], cmd[150];

    port = char_to_num(argv[3]);

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //* tcp socket
    s_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (s_fd < 0) fail_err("Failed to create TCP socket");

    //* disable Nagle algorithm
    const bool disable_flag = true;
    int ret = setsockopt(s_fd, IPPROTO_TCP, TCP_NODELAY,
                         (char *) &disable_flag, sizeof(int));

    if (ret) fail_err("Failed to stop the Nagle algorithm");

    if (connect(s_fd, (s_ad *) &server, sizeof(server)) < 0)
        fail_err("Client can't connect to the server");

    //* send the id and check if it already exists
    if (send(s_fd, argv[1], strlen(argv[1]), 0) < 0)
        fail_err("Client can't send the id");

    bool flag;
    recv(s_fd, &flag, sizeof(bool), 0);

    if (flag) return 0;

    poll_fd p_fds[1000];

    p_fds[0] = (poll_fd) {.fd = STDIN_FILENO, .events = POLLIN};
    p_fds[1] = (poll_fd) {.fd = s_fd, .events = POLLIN};
    fds = 2;

    while (true) {
        poll(p_fds, fds, -1);

        bytes_received = 0;

        strcpy(msg, "");

        short flags[2];

        flags[0] = p_fds[0].revents & POLLIN;  //* stdin
        flags[1] = p_fds[1].revents & POLLIN;  //* tcp

        // printf("1 -> %d 2 -> %d\n", flags[0], flags[1]);

        if (flags[0]) {  //* stdin
            if (fgets(cmd, 150, stdin)) {
                if (!strcmp(cmd, "exit\n")) {
                    close(s_fd);
                    return 0;
                }

                if (send(s_fd, cmd, 150, 0) < 0)
                    fail_err("Client can't send a message");

                char *p = strtok(cmd, " ");

                if (!p) continue;

                if (!strcmp(p, "subscribe")) {
                    p = strtok(NULL, "\n");
                    printf("Subscribed to topic %s.\n", p);
                }

                if (!strcmp(p, "unsubscribe")) {
                    p = strtok(NULL, "\n");
                    printf("Unsubscribed to topic %s.\n", p);
                }
            }
            continue;
        }

        if (flags[1]) {  //* tcp
            //? find size of message
            bytes_received = recv(s_fd, &msg_size, sizeof(int), 0);
            if (bytes_received < 0) fail_err("Client can't read message size");

            //? read message
            bytes_received = recv(s_fd, msg, msg_size, 0);
            if (bytes_received < 0) fail_err("Client failed to receive message");

            //* check if client is stopped
            if (!strcmp(msg, "exit\n")) {
                close(s_fd);
                return 0;
            }

            //* print message
            Message *post = (Message *) msg;

            char *to_split = post->msg;

            type = 0;
            memcpy(&type, to_split + 50, 1);

            printf("%s:%i - ", inet_ntoa(post->client_addr.sin_addr),
                               ntohs(post->client_addr.sin_port));

            printf("%s - ", post->topic);

            switch (type) {
                case 0:  //* INT
                    uint32_t n_int;
                    uint8_t sign_int;

                    memcpy(&sign_int, to_split + 51, 1);
                    memcpy(&n_int, to_split + 52, sizeof(uint32_t));

                    n_int = ntohl(n_int);

                    if (sign_int) n_int *= -1;

                    printf("INT - %d\n", n_int);
                    break;
                case 1:  //* SHORT_REAL
                    float n_short;
                    uint16_t num_short = 0;

                    memcpy(&num_short, to_split + 51, sizeof(uint16_t));

                    n_short = ntohs(num_short);
                    n_short /= 100.;

                    printf("SHORT_REAL - %.4f\n", n_short);
                    break;
                case 2:  //* FLOAT
                    float n_real;
                    uint32_t num_real;
                    uint8_t sign_real = 0, exponent = 0;

                    memcpy(&sign_real, to_split + 51, 1);
                    memcpy(&num_real, to_split + 52, sizeof(uint32_t));
                    memcpy(&exponent, to_split + 56, 1);

                    n_real = ntohl(num_real);
                    n_real /= pow(10., exponent);

                    if (sign_real) n_real *= -1;

                    printf("FLOAT - %.4f\n", n_real);
                    break;
                case 3:  //* STRING
                    char m[2500];

                    memcpy(m, to_split + 51, post->len - 50);
                    printf("STRING - %s\n", m);

                    break;
                default:
                    fail_err("Type is not in 0-3");
            }
        }
    }

    return 0;
}