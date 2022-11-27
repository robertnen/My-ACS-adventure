#include <stdio.h>
#include <math.h>

const float PI = 3.14159265;

void anglesCalculatorWithVectors(float edges[], float angles[]);
void anglesCalculatorWithoutVectors(float edge_1, float edge_2, float edge_3, float* angle_1, float* angle_2, float* angle_3);

int main() {

    float edges[3], angles[3];

    //citire
    scanf("%f%f%f", &edges[0], &edges[1], &edges[2]);

    //functia care afla unghiurile folosind vectori
    anglesCalculatorWithVectors(edges, angles);

    //afisare
    printf("%.3f %.3f %.3f\n", angles[0] / PI * 180, angles[1] / PI * 180, angles[2] / PI * 180);

    //functia care afla unghiurile fara a folosi vectori
    anglesCalculatorWithoutVectors(edges[0], edges[1], edges[2], &angles[0], &angles[1], &angles[2]);

    //afisare
    printf("%.3f %.3f %.3f\n", angles[0] / PI * 180, angles[1] / PI * 180, angles[2] / PI * 180);

    return 0;
}

//calculeaza unghiurile folosind vectori
void anglesCalculatorWithVectors(float edges[], float angles[]) {

    //folosesc formula
    // <(b, c) = arccos((b * b + c * c - a * a) / (2 * b * c);

    //ca sa nu mai inmultesc de 6 ori le tin minte
    float edge_1, edge_2, edge_3;

    edge_1 = edges[0] * edges[0];
    edge_2 = edges[1] * edges[1];
    edge_3 = edges[2] * edges[2];

    angles[0] = acos( (edge_2 + edge_3 - edge_1) / (2 * edges[1] * edges[2]));
    angles[1] = acos( (edge_1 + edge_3 - edge_2) / (2 * edges[0] * edges[2]));
    angles[2] = acos( (edge_1 + edge_2 - edge_3) / (2 * edges[0] * edges[1]));

}

//calculeaza unghiurile fara a folosi vectori
void anglesCalculatorWithoutVectors(float edge_1, float edge_2, float edge_3, float* angle_1, float* angle_2, float* angle_3) {

    //fac analog ca mai sus

    float e1, e2, e3;

    e1 = edge_1 * edge_1;
    e2 = edge_2 * edge_2;
    e3 = edge_3 * edge_3;

    (*angle_1) = acos( (e2 + e3 - e1) / (2 * edge_2 * edge_3));
    (*angle_2) = acos( (e1 + e3 - e2) / (2 * edge_1 * edge_3));
    (*angle_3) = acos( (e1 + e2 - e3) / (2 * edge_1 * edge_2));

}