#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

typedef struct {
    char *username, *password;
} Credentials;

typedef struct {
    char title[350], author[350], genre[350];
    char publisher[350], pages_num[350];
} Book;

//* data for connection
char host[] = "34.246.184.49";
const uint32_t PORT = 8080;
const uint32_t MAX = 350;

char payload[] = "application/json";

//* paths for api
const char SRC_API[] = "/api/v1/tema/";
const char PATHS[][20] = {"auth/register", "auth/login", "auth/logout",
                            "library/access", "library/books"};

//* commands
const char CMD_ACC[][20] = {"register", "login", "logout", "exit"};
const char CMD_LIB[][20] = {"enter_library", "add_book", "get_book",
                            "get_books", "delete_book"};

/* 4xx and 500 codes
* these are not the error codes, they are the indexes
*  0 -        register |  1 -  user exists conflict |  2 -        invalid login
*  3 -    invalid auth |  4 -           failed auth |  5 - user exists conflict
*  6 -      invalid id |  7 -   invalid information |  8 -        access denied
*  9 -    user refused | 10 -  book exists conflict | 11 -              timeout
* 12 - invalid command | 13 -           server fail | 14 -        empty library
* 15 -    invalid book | 16 -  delete access denied
*/
const char ERRS[][50] = {"[ERROR 400] Invalid register data.\n",
                         "[ERROR 409] User already exists.\n",
                         "[ERROR 422] Invalid login data.\n",
                         "[ERROR 422] Invalid authentification.\n",
                         "[ERROR 401] Failed to authentificate.\n",
                         "[ERROR 409] User already on the server.\n",
                         "[ERROR 404] Invalid id.\n",
                         "[ERROR 422] Invalid page count.\n",
                         "[ERROR 403] Access denied to library.\n",
                         "[ERROR 400] Empty fields found.\n",
                         "[ERROR 409] Book already exists.\n",
                         "[ERROR 408] Timeout.\n",
                         "[ERROR 400] Invalid command.\n",
                         "[ERROR 500] Internal server error.\n",
                         "[ERROR 404] Library is empty.\n",
                         "[ERROR 404] Book doesn't exist.\n",
                         "[ERROR 404] Book can't be deleted.\n"};

/* 2xx
* these are not the success codes, they are the indexes
* 0 - register | 1 -     log in | 2 -   disconnect
* 3 -   access | 4 - book added | 5 - book deleted
*/
const char SUCS[][50] = {"[SUCCESS 201] User is registered.\n",
                         "[SUCCESS 200] User successfully logged in.\n",
                         "[SUCCESS 200] User successfully disconnected.\n",
                         "[SUCCESS 200] User has access to the library.\n",
                         "[SUCCESS 201] Book successfully added.\n",
                         "[SUCCESS 201] Book successfully deleted.\n"};

//* used for cookie library access
const char TOKEN[] = "{\"token\":\"";
const char TITLE[] = "\"title\":\"";

//? replaces the first occurence of new line with null terminator
void remove_end_line(char* cmd, int max_size) {
    for (int i = 0; cmd[i] != '\0' && i < max_size; i++)
        if (cmd[i] == '\n') {
            cmd[i] = '\0';
            return;
        }
}

//? checks if it is an account command
bool is_cmd_acc(char* cmd) {
    for (int i = 0; i < 4; i++)
        if (!strcmp(cmd, CMD_ACC[i])) return true;

    return false;
}

//? checks if it is a library command
bool is_cmd_lib(char* cmd) {
    for (int i = 0; i < 5; i++)
        if (!strcmp(cmd, CMD_LIB[i])) return true;

    return false;
}

//? creates a new user and makes a json string
char* get_user_credentials(bool flag) {
    Credentials user;
    char *serialized;

    user.username = (char *) calloc(MAX, 1);
    user.password = (char *) calloc(MAX, 1);

    /* read the format:
    *  username=
    *  password=
    */
    printf("username="); fgets(user.username, MAX, stdin);
    printf("password="); fgets(user.password, MAX, stdin);

    remove_end_line(user.username, MAX);
    remove_end_line(user.password, MAX);

    //* true - register | false - login
    //? invalid register / login, send error code
    if (strlen(user.username) * strlen(user.password) == 0 ||
        strchr(user.username, ' ') || strchr(user.password, ' ')) {
            printf("%s", ERRS[flag ? 0 : 2]);
            return NULL;
        }

    JSON_Value *data = json_value_init_object();
    JSON_Object *obj = json_value_get_object(data);

    json_object_set_string(obj, "username", user.username);
    json_object_set_string(obj, "password", user.password);

    serialized = json_serialize_to_string_pretty(data);

    //* free the calloc
    free(user.username);
    free(user.password);
    json_value_free(data);

    return serialized;
}

//? gets the token out of a cookie
char* get_token(char* cookie) {
    char *start, *end, *token;

    start = strrchr(cookie, '"');
    *start = '\0';

    end = strrchr(cookie, '"');
    token = end + 1;

    memmove(cookie, token, strlen(token) + 1);

    return cookie;
}

//? creates a new book
void get_book(Book* book) {
    printf("title="); fgets((*book).title, MAX, stdin);
    printf("author="); fgets((*book).author, MAX, stdin);
    printf("genre="); fgets((*book).genre, MAX, stdin);
    printf("publisher="); fgets((*book).publisher, MAX, stdin);

    char input[MAX];
    bool isValid = true;

    printf("page_count="); fgets(input, MAX, stdin);

    //! check if input is valid
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {isValid = false; break;}
        if ('a' <= input[i] && input[i] <= 'z') {isValid = false; break;}
        if ('A' <= input[i] && input[i] <= 'Z') {isValid = false; break;}
    }

    if (!isValid || atoi(input) <= 0) {
        printf("%s", ERRS[7]);
        book = NULL;
        return;
    }

    strcpy((*book).pages_num, input);

    //* remove new line from the book fields
    remove_end_line((*book).title, MAX);
    remove_end_line((*book).author, MAX);
    remove_end_line((*book).genre, MAX);
    remove_end_line((*book).publisher, MAX);
    remove_end_line((*book).pages_num, MAX);
}

//? gets all the books from the library
char* get_library_books(int sock_fd, char* token) {
    char *msg, path[50];

    strcpy(path, SRC_API);
    strcat(path, PATHS[4]);

    msg = make_get_request(host, path, token, NULL, NULL, 0);
    send_to_server(sock_fd, msg);

    char *books = receive_from_server(sock_fd);

    if (!books) {
        printf("%s", ERRS[13]);
        return NULL;
    }

    return books;
}

//? adds the book to the server
void send_book(int sock_fd, Book book, char* token) {
    JSON_Value *data = json_value_init_object();
    JSON_Object *book_json = json_value_get_object(data);

    json_object_set_string(book_json, "title", book.title);
    json_object_set_string(book_json, "author", book.author);
    json_object_set_string(book_json, "genre", book.genre);
    json_object_set_string(book_json, "page_count", book.pages_num);
    json_object_set_string(book_json, "publisher", book.publisher);

    char *serialized_data = json_serialize_to_string_pretty(data);
    char msg[1000], tmp[1000], *ans;

    //* create the POST request
    sprintf(msg, "POST %s%s HTTP/1.1\r\n", SRC_API, PATHS[4]);

    sprintf(tmp, "Host: %s\r\n", host);
    strcat(msg, tmp);

    sprintf(tmp, "Content-Type: %s\r\n", payload);
    strcat(msg, tmp);

    sprintf(tmp, "Connection: open\r\nAuthorization: Bearer %s\r\n", token);
    strcat(msg, tmp);

    sprintf(tmp, "Content-Length: %ld\r\n\r\n", strlen(serialized_data));
    strcat(msg, tmp);
    strcat(msg, serialized_data);

    //* send it
    send_to_server(sock_fd, msg);
    ans = receive_from_server(sock_fd);

    //* check output
    if (strstr(ans, "ok")) printf("%s", SUCS[4]);
    if (strstr(ans, "Timeout")) printf("%s", ERRS[11]);
}

//? gets the book from the server
bool get_book_by_id(int sock_fd, char* token, int id, bool isMuted) {
    char msg[1000], tmp[1000], *book;

    //* create the POST request
    sprintf(msg, "GET %s%s/%d HTTP/1.1\r\n", SRC_API, PATHS[4], id);

    sprintf(tmp, "Host: %s\r\n", host);
    strcat(msg, tmp);

    sprintf(tmp, "Content-Type: %s\r\n", payload);
    strcat(msg, tmp);

    sprintf(tmp, "Connection: open\r\nAuthorization: Bearer %s\r\n\r\n", token);
    strcat(msg, tmp);

    send_to_server(sock_fd, msg);
    book = receive_from_server(sock_fd);

    book = strchr(book, '{');

    if (!isMuted) {
        if (strstr(book, "No")) printf("%s", ERRS[15]);
        else printf("%s", book);
    }

    if (strstr(book, "No")) return false;
    return true;
}

//? deletes the book from the server
void delete_book(int sock_fd, char* token, int id) {
    char msg[1000], tmp[1000], *ans;

    //* create the POST request
    sprintf(msg, "DELETE %s%s/%d HTTP/1.1\r\n", SRC_API, PATHS[4], id);

    sprintf(tmp, "Host: %s\r\n", host);
    strcat(msg, tmp);

    sprintf(tmp, "Connection: open\r\nAuthorization: Bearer %s\r\n\r\n", token);
    strcat(msg, tmp);

    send_to_server(sock_fd, msg);
    ans = receive_from_server(sock_fd);

    if (strstr(ans, "No")) printf("%s", ERRS[16]);
    else printf("%s", SUCS[5]);
}

int main() {
    int sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
    char *data, *cookie = NULL, *token = NULL, *cookie_lib = NULL;
    char tmp[4096];

    bool isLogged = false;

    if (sock_fd < -1) {
        fprintf(stderr, "Connection failed.\n");
        return 0;
    }

    while (true) {
        char *cmd = (char *) calloc(MAX, 1);
        fgets(cmd, MAX, stdin);

        remove_end_line(cmd, MAX);

        //* flags to check the command
        bool flags[2] = {is_cmd_acc(cmd), is_cmd_lib(cmd)};

        //* invalid command, try again
        if (flags[0] == false && flags[1] == false) {
            printf("%s", ERRS[12]);
            //* new post
            sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
            continue;
        }

        //* account commands
        if (flags[0]) {
            if (!strcmp(cmd, CMD_ACC[0])) {  //* register
                data = get_user_credentials(true);

                if (!data) {
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                char *msg, path[50] = "";

                strcpy(path, SRC_API);
                strcat(path, PATHS[0]);

                msg = compute_post_request(host, path, payload,
                                            &data, 1, NULL, 0);

                send_to_server(sock_fd, msg);

                printf("%s", strstr(receive_from_server(sock_fd), "ok")
                                ? SUCS[0] : ERRS[1]);
            }
            if (!strcmp(cmd, CMD_ACC[1])) {  //* log in
                if (isLogged) {
                    printf("%s", ERRS[5]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                data = get_user_credentials(false);
                if(!data) {
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                char *msg, path[50] = "";

                strcpy(path, SRC_API);
                strcat(path, PATHS[1]);

                msg = compute_post_request(host, path, payload,
                                            &data, 1, NULL, 0);

                send_to_server(sock_fd, msg);

                char *tmp = receive_from_server(sock_fd);
                bool flag = strstr(tmp, "ok");

                printf("%s", flag ? SUCS[1] : ERRS[3]);

                //? "cookie": "Set-Cookie: connect.sid=..."
                //? but it has after "; Path=/; HttpOnly..."
                if (flag) {
                    cookie = strstr(tmp, "connect.sid=");

                    if (cookie)
                        cookie[strchr(cookie, ';') - cookie] = '\0';

                    isLogged = true;
                }
            }
            if (!strcmp(cmd, CMD_ACC[2])) {  //* log out
                if (!isLogged) {
                    printf("%s", ERRS[4]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                char *msg, path[50] = "";

                strcpy(path, SRC_API);
                strcat(path, PATHS[2]);

                msg = compute_get_request(host, path, NULL, &cookie, 1);
                send_to_server(sock_fd, msg);

                if (strstr(receive_from_server(sock_fd), "ok")) {
                    data = NULL;
                    token = NULL;
                    cookie = NULL;
                    cookie_lib = NULL;
                    isLogged = false;
                    printf("%s", SUCS[2]);
                } else printf("%s", ERRS[4]);

            }
            if (!strcmp(cmd, CMD_ACC[3])) break;  //* exit

            //* new post
            sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
        }

        //* library commands
        if (flags[1]) {
            if (!strcmp(cmd, CMD_LIB[0])) {  //* enter library
                if (!isLogged) {  //* user is not authentificated
                    printf("%s", ERRS[4]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                char *msg, path[50] = "";

                strcpy(path, SRC_API);
                strcat(path, PATHS[3]);

                msg = compute_get_request(host, path, NULL, &cookie, 1);
                send_to_server(sock_fd, msg);

                cookie_lib = strstr(receive_from_server(sock_fd), TOKEN);

                printf("%s", cookie_lib ? SUCS[3] : ERRS[8]);

                //* new post
                sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                continue;
            }

            if (!cookie_lib) {
                printf("%s", ERRS[8]);
                //* new post
                sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                continue;
            }

            if (!strcmp(cmd, CMD_LIB[1])) {  //* add book
                strcpy(tmp, cookie_lib);
                token = get_token(tmp);

                Book book;

                get_book(&book);

                //* check for empty fields
                if (book.title[0] == '\0' || book.author[0] == '\0' ||
                    book.genre[0] == '\0' || book.publisher[0] == '\0' ||
                    book.pages_num[0] == '\0') {
                        printf("%s", ERRS[9]);

                        //* new post
                        sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                        continue;
                    }

                char* books = get_library_books(sock_fd, token);

                //! internal server error so don't do anything
                if (!books) {
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                char tmp[1000];

                strcpy(tmp, TITLE);
                strcat(tmp, book.title);
                strcat(tmp, "\"");

                //* book already exists
                if (strstr(books, tmp)) {
                    printf("%s", ERRS[10]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                //* add book
                send_book(sock_fd, book, token);
            }
            if (!strcmp(cmd, CMD_LIB[2])) {  //* get book
                char id[MAX];

                printf("id="); fgets(id, MAX, stdin);
                id[strlen(id)] = '\0';

                int pos = -1;

                //* check if there are spaces
                for (int i = 0; i < (int) strlen(id); i++)
                    if (id[i] == ' ') {
                        pos = i;
                        break;
                    }

                //* id contains spaces or not a number
                if (pos != -1 || atoi(id) <= 0) {
                    printf("%s", ERRS[6]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                strcpy(tmp, cookie_lib);
                token = get_token(tmp);

                get_book_by_id(sock_fd, token, atoi(id), false);
            }
            if (!strcmp(cmd, CMD_LIB[3])) {  //* get books
                strcpy(tmp, cookie_lib);
                token = get_token(tmp);

                char* books = get_library_books(sock_fd, token);

                //! internal server error so don't do anything
                if (!books) continue;

                if (books[1] == ']') {
                    printf("%s", ERRS[14]);
                    continue;
                }

                char tmp[1000] = "[SUCCESS 200] \"books\": ";

                strcat(tmp, books);
                printf("%s", books);
            }
            if (!strcmp(cmd, CMD_LIB[4])) {  //* delete book
                char id[MAX];

                printf("id="); fgets(id, MAX, stdin);
                id[strlen(id)] = '\0';

                int pos = -1;

                //* check if there are spaces
                for (int i = 0; i < (int) strlen(id); i++)
                    if (id[i] == ' ') {
                        pos = i;
                        break;
                    }

                //* id contains spaces or not a number
                if (pos != -1 || atoi(id) <= 0 || (id[0] < '0' || id[0] > '9')) {
                    printf("%s", ERRS[6]);
                    //* new post
                    sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
                    continue;
                }

                strcpy(tmp, cookie_lib);
                token = get_token(tmp);

                //* check if book exists
                if (get_book_by_id(sock_fd, token, atoi(id), true))
                    delete_book(sock_fd, token, atoi(id));
            }

            //* new post
            sock_fd = open_connection(host, PORT, AF_INET, SOCK_STREAM, 0);
        }
    }

    //* closing the connection
    close(sock_fd);

    token = NULL;
    cookie = NULL;
    cookie_lib = NULL;

    return 0;
}