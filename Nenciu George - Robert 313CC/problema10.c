#include <stdio.h>

int main() {

    int hour, minute, second;

    if(scanf("%d%d%d", &hour, &minute, &second) == 3)
        printf("%0.2d:%0.2d:%0.2d\n", hour, minute, second);
    else printf("Date introduse incorect\n");

    return 0;
}