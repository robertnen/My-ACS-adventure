#include <stdio.h>

struct multime {

    unsigned char a;
};

void init(struct multime* m);
void add(struct multime* m, int x);
void del(struct multime* m, int x);
void print(struct multime* m);
int contains(struct multime* m, int x);

int main() {

    struct multime m;
    init(&m);
    add(&m, 1);
    print(&m);

    return 0;
}

void init(struct multime* m) {

    m->a = 0;
}

void add(struct multime* m, int x) {

    m->a = m->a | (2 << x);
}

void del(struct multime* m, int x) {

    m->a = m->a ^ (2 << x);
    m->a = m->a ^ (2 << x); //daca bitul era 1, acum e 0

}
/*
    0 1 2 3 4 5 6 7
    0 0 0 0 1 0 0 0
*/
void print(struct multime* m) {

    for(int i = 7; i > -1; i--) {

         if(m->a >= (2 << i)) printf("%d %d %d\n", i, (2 << i), m->a);

    } 
}

int contains(struct multime* m, int x) {

    return (m->a & x) ? 1 : 0;
}
