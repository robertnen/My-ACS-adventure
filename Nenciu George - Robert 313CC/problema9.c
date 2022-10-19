#include <stdio.h>

int main() {

    int hour, minute, second;

    scanf("%d%d%d", &hour, &minute, &second);

    printf("%0.2d:%0.2d:%0.2d", hour, minute, second);

    return 0;
}