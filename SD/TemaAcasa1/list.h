/* NENCIU George-Robert - 313CC */
#ifndef LIST_H
#define LIST_H
                                /* Noduri */
typedef struct Node {                           //pentru "banda magica"
    struct Node *next, *prev;
    unsigned char ch;
} Node;

typedef struct Node2 {                          //pentru stivele Undo / Redo
    struct Node2 *next, *prev;
    Node *nptr;                                 //nptr retine pozitia degetului
} Node2;

typedef struct Node3 {                          //pentru coada
    struct Node3 *next, *prev;
    char text[20];                              //text tine minte comanda
} Node3;

                       /*Lista, stiva si coada*/
typedef struct {
    Node *head, *finger;
    int total;
} List;                                        //"banda magica"

typedef struct {
    Node2 *last, *top;
    int total;
} Stack;                                        //pentru Undo / Redo

typedef struct {
    Node3 *front, *rear;
    int total;
} Queue;                                        //pentru execute

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
void enqueue(Queue* queue, char* text);
char* frontQueue(Queue* queue);
void dequeue(Queue* queue);
void freeQueue(Queue* queue);

#endif