/* NENCIU George-Robert - 313CC */
#ifndef LIST_H
#define LIST_H
                                /* Noduri */
typedef struct Node {
    struct Node *next, *prev;
    unsigned char ch;
} Node;

typedef struct Node2 {
    struct Node2 *next, *prev;                  //nptr ajuta la coada / stiva
    Node *nptr;
} Node2;

typedef struct Node3 {
    struct Node3 *next, *prev;                  //text tine minte comanda
    char text[20];
} Node3;

                       /*Lista, stiva si coada*/
typedef struct {
    Node *head;
    int total;                                 //total e nr. de elemente
} List;

typedef struct {
    Node2 *last, *top;
    int total;
} Stack;

typedef struct {
    Node3 *front, *rear;
    int total;
} Queue;

Node* createNode(unsigned char ch);

                            /*Lista*/
List* initLista();
Node* addNode(List* list, int pos, unsigned char ch);
void remNode(List* list, int pos);
void freeList(List* list);

                            /*Stiva*/
Stack* initStack();
int pushStack(Stack* stack, Node* finger);
int popStack(Stack** stack);
Node* topStack(Stack* stack);
void freeStack(Stack* stack, int length);

                            /*Coada*/
Queue* initQueue();
void addQueue(Queue* queue, char* text);
char* frontQueue(Queue* queue);
void remQueue(Queue* queue);
void freeQueue(Queue* queue);

#endif