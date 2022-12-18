#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 32

struct multime {

    unsigned int n;
    unsigned char* a;
};

int cmpFunc(const void* x, const void* y) { return (*(int*)x - *(int*)y); }

void init(struct multime* m);
void add(struct multime* m, int x);
void del(struct multime* m, int x);
void print(struct multime* m);
int contains(struct multime* m, int x);

int main() {

    struct multime m;
    int n, x;
    char operation;

    scanf("%d", &n);

    init(&m);

    for(int i = 0; i < n; i++) {

        scanf(" %c", &operation);

       if(operation == 'P') print(&m);
       else {

            scanf(" %d", &x);

            if(operation == 'A') add(&m, x);
            else if(operation == 'D') del(&m, x);
                else printf(contains(&m, x) ? "Da\n": "Nu\n");
       }
    }

    free(m.a);

    return 0;
}

void init(struct multime* m) {

    m->n = MAX_SIZE;

    m->a = (unsigned char*) calloc(m->n, sizeof(unsigned char));
}

void add(struct multime* m, int x) {

    int pos = x / 8; 

    m->a[pos] = m->a[pos] | (1 << (x % 8));

}

void del(struct multime* m, int x) {

    unsigned char aux = m->a[x / 8];

    m->a[x / 8] = m->a[x / 8] ^ (1 << (x % 8));
    
    if(aux < m->a[x / 8]) m->a[x / 8] = aux; // nu exista acel element
}

void print(struct multime* m) {

    int log, pow, count = -1, sol[MAX_SIZE] = {0};
    unsigned char aux;

    for(int i = 0; i < m->n / 8; i++) {

        aux = m->a[i];
        pow = 1;
        log = 0;

        while(m->a[i] >= pow) { //caut prima putere care depaseste numarul

            pow <<= 1;
            log++;
        }

        pow >>= 1;
        log--;

        while(m->a[i] > 0) { //scot fiecare bit de 1

            if(m->a[i] >= pow) {

                sol[++count] = log + i * 8;
                m->a[i] -= pow;
            }

            pow >>= 1;
            log--;
        }

        m->a[i] = aux;
        
    }

    qsort(sol, count, sizeof(int), cmpFunc);

    for(int i = 0; i <= count; i++) printf("%d ", sol[i]);

    printf("\n");
}

int contains(struct multime* m, int x) {

    return (m->a[x / 8] & (1 << (x % 8))) ? 1 : 0;
}
