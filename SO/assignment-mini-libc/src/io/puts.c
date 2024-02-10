#include <../include/stdio.h>
#include <unistd.h>

int puts(const char *str) {
    int i = 0;
    while (str[i++]) continue; // I want to get strlen(str)
    write(1, str, i);
    write(1, "\n", 1);

    return i + 1; // how many characters in str
}
