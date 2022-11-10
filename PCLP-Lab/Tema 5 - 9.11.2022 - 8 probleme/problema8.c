#include <stdio.h>

int arie_intersectie(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);

int main() {
    
    int x11, y11, x12, y12, x21, y21, x22, y22;

    //citire
    scanf("%d%d%d%d%d%d%d%d", &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22);

    //afisare
    printf("%d\n", arie_intersectie(x11, y11, x12, y12, x21, y21, x22, y22));

    return 0;

}

//calculeaza suprafata comuna a doua dreptunghiuri
//sunt mai multe commenturi jos pentru ca ma incurcam in formule si ma ajutau
int arie_intersectie(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    int x1, y1, x2, y2;

    //verific daca se intersecteaza
    if(x21 > x12 || x22 < x11) return 0;
    if(y21 < y12 || y22 > y11) return 0;

    //"fixez" primul triunghi si incerc sa vad unde se afla relativ al doilea
    //folosind coordontale colturilor
    if(x21 >= x11 || x21 <= x12) {

        //zona comuna incepe de la x = x21 in stanga-sus
        x1 = x21;

        //verific daca cumva dreptunghiul e inclus in cel "fixat"
        //daca nu, atunci zona se opreste in x = x12
        if(x12 > x22) x2 = x22;
        else x2 = x12;

    } // restul se rezolva analog ca ce e mai sus
    else {
  
        x1 = x22;
        if(x11 > x21) x2 = x22;
        else x2 = x12;
    } 

    if(y21 <= y11 || y21 >= y12) {
    
        y1 = y21;
        if(y12 > y22) y2 = y12;
        else y2 = y22;

    }
    else {
        
        y1 = y22;
        if(y11 > y21) y2 = y12;
        else y2 = y22;
        
    } 

    //l1 si l2 reprezinta dimensiunile dreptunghiului format de cele doua (daca exista)
    int l1, l2;

    //suprafata comuna este un dreptunghi format din colturile cu coordonatele:
    // stanga-sus:  (x1, y1), stanga-jos:  (x1, y2)
    // dreapta-sus: (x2, y1), dreapta-jos: (x2, y2)
    // => l1 = sqrt((x1 - x1) ^ 2 + (y2 - y1) ^ 2) = sqrt((y2 - y1) ^ 2) = abs(y2 - y1);
    // analog l2 = abs(x2 - x1);
    l1 = y1 - y2;
    l2 = x1 - x2;
    
    if(l1 < 0) l1 *= -1;
    if(l2 < 0) l2 *= -1;

    return l1 * l2;

}
