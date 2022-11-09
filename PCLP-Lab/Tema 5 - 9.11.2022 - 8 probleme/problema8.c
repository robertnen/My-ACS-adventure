#include <stdio.h>

int arie_intersectie(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);

int main() {
    
    int x11, y11, x12, y12, x21, y21, x22, y22;

    scanf("%d%d%d%d%d%d%d%d", &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22);

    printf("%d\n", arie_intersectie(x11, y11, x12, y12, x21, y21, x22, y22));

    return 0;

}

int arie_intersectie(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    int x1, y1, x2, y2;

    //daca nu se intersecteaza
    if(x21 > x12 || x22 < x11) return 0;
    if(y21 < y12 || y22 > y11) return 0;

    if(x21 >= x11 || x21 <= x12) {

        x1 = x21;
        if(x12 > x22) x2 = x22;
        else x2 = x12;

    }
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

    int l1, l2;

    l1 = y1 - y2;
    l2 = x1 - x2;
    
    if(l1 < 0) l1 *= -1;
    if(l2 < 0) l2 *= -1;

    return l1 * l2;

}
