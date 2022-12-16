#include <stdio.h>
#include <time.h>

char* timestr(struct tm t, char* timeC) {

    time_t today = time(&today);

    t = (*localtime(&today));

    int hour, minute, second, day, month, year;

    hour = t.tm_hour;
    minute = t.tm_min;
    second = t.tm_sec;

    int length = 0;

    if(hour > 9) {

        timeC[length++] = hour / 10 + '0';
        timeC[length++] = hour % 10 + '0';

    } else {

        timeC[length++] = '0';
        timeC[length++] = hour + '0';

    }

    timeC[length++] = ':';

    if(minute > 9) {

        timeC[length++] = minute / 10 + '0';
        timeC[length++] = minute % 10 + '0';

    } else {

        timeC[length++] = '0';
        timeC[length++] = minute + '0';

    }

    timeC[length++] = ':';
    
    if(second > 9) {

        timeC[length++] = second / 10 + '0';
        timeC[length++] = second % 10 + '0';

    } else {

        timeC[length++] = '0';
        timeC[length++] = second + '0';

    }

    timeC[length] = '\0';

    return timeC;

}

int main() {

    struct tm t; char time[100];

    timestr(t, time);

    printf("Ora este %s.\n", time);

    return 0;
}