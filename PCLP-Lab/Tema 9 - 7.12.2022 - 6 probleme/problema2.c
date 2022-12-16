#include <stdio.h>
#include <time.h>

int main() {

    time_t today = time(&today);

    struct tm* tm_info = localtime(&today);

    int hour, minute, second, day, month, year;

    hour = tm_info->tm_hour;
    minute = tm_info->tm_min;
    second = tm_info->tm_sec;
    day = tm_info->tm_mday;
    month = tm_info->tm_mon + 1;
    year = tm_info->tm_year + 1900;

    printf("Ora: %d:%d:%d", hour, minute, second);

    printf("\nData: %d/%d/%d", day, month, year);

    return 0;
}