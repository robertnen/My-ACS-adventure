#include <stdio.h>
#include <math.h>


float dist(int x1, int y1, int x2, int y2);

int main() {

    //in cele 4 variabile se retin cele 2 puncte care implica cea mai mare distanta
    int iPos_x, iPos_y, fPos_x, fPos_y;
    float maxDist, distance;

    //tin mintele coordonatele
    int x_points[101];
    int y_points[101];

    maxDist = -1; // nu exista distanta negativa

    int n;

    //citire
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d%d", &x_points[i], &y_points[i]);

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++) {
            
            distance = dist(x_points[i], y_points[i], x_points[j], y_points[j]);

            if(distance > maxDist) {

                    maxDist = distance;

                    iPos_x = x_points[i];
                    iPos_y = y_points[i];

                    fPos_x = x_points[j];
                    fPos_y = y_points[j];
            }
        }

    //afisare
    printf("%d %d\n%d %d\n%f\n", iPos_x, iPos_y, fPos_x, fPos_y, maxDist);
    
    return 0;

}

//distanta intre doua puncte
float dist(int x1, int y1, int x2, int y2) {

    return sqrt((x2 * 1. - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

}