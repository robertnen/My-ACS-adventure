#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void * data;
    struct Node *next, *prev;
} Node;

typedef struct TDoubleLinkedList {
    Node *head, *tail;
    int len;
} TDoubleLinkedList;

typedef TDoubleLinkedList List;

List* init();                                   //done
void add(List* list, int pos, void* data);      //done
void removeNode(List* list, int pos);           //done
void freeList(List* list);                      //done
void printInt(List* list);                      //done
void printString(List* list);                   //done
void print_reversedInt(List *list);             //done
void print_reversedString(List *list);          //done
void add_in_order(List *list, void* data);      //done

int main() {

    List* list = init();
    int v[] = {7, 6, 5, 4, 3, 2, 1};
    for(int i = 0; i < 7; i++) add(list, 1, &v[i]);
    printInt(list);
    // printString(list);
    // print_reversedString(list);
    removeNode(list, 7);
    removeNode(list, 6);
    print_reversedInt(list);
    printInt(list);
    add_in_order(list, &v[3]);
    printInt(list);
    freeList(list);
    return 0;
}

List* init() {
    List *list = (List*) calloc(1, sizeof(List));
    list->head = (Node*) calloc(1, sizeof(Node));
    list->tail = (Node*) calloc(1, sizeof(Node));
    list->head->next = list->tail;
    list->tail->prev = list->head;
    return list;
}

void freeList(List* list) {
    Node *p = list->tail->prev, *q;
    while(p->prev) {
        q = p;
        p = p->prev;
        free(q);
    }
    free(list->tail);
    free(list->head);
    free(list);
}

void add(List* list, int pos, void* data) {
    Node *new = calloc(1, sizeof(Node)), *p;
    new->data = data;
    list->len++;
    if(pos - 1 > list->len - pos) {
        if(pos == list->len) {
            list->tail->prev->next = new;
            new->prev = list->head->prev;
            new->next = list->tail;
            list->tail->prev = new;
        } else {
            p = list->tail->prev;
            pos = list->len - pos;
            while(pos--) p = p->prev;
            new->prev = p->prev;
            new->next = p;
            p->prev->next = new;
            p->prev = new;
        }
    } else {
        p = list->head->next;
        if(pos == 1) {
            new->next = list->head->next;
            new->prev = list->head;
            list->head->next->prev = new;
            list->head->next = new;
        } else {
            p = list->head;
            pos--;
            while(pos--) p = p->next;
            new->next = p->next;
            new->prev = p;
            p->next->prev = new;
            p->next = new;
        }
    }
}

void removeNode(List* list, int pos) {
    Node *p = list->head, *q;
    while(pos-- > 1) p = p->next;
    q = p->next;
    p->next = q->next;
    q->next->prev = p;
    free(q);
    list->len--;
}

void printInt(List* list) {
    Node *p = list->head->next;
    while(p->next) {
        printf("%d ", *(int*)p->data);
        p = p->next;
    }
    printf("\n");
}

void printString(List* list) {
    Node *p = list->head->next;
    while(p->next) {
        printf("%c ", *(char*)p->data);
        p = p->next;
    }
    printf("\n");
}

void print_reversedInt(List *list) {
    Node *p = list->tail->prev;
    while(p->prev) {
        printf("%d ", *(int*)p->data);
        p = p->prev;
    }
    printf("\n");
}

void print_reversedString(List *list) {
    Node *p = list->tail->prev;
    while(p->prev) {
        printf("%c ", *(char*)p->data);
        p = p->prev;
    }
    printf("\n");
}

void add_in_order(List *list, void* data) {
    Node *new = (Node*) calloc(1, sizeof(Node)), *p;
    new->data = data;
    p = list->head->next;
    while(*(int*)p->data < *(int*)data && p->next->next) p = p->next;
    new->next = p->next;
    new->prev = p;
    p->next->prev = new;
    p->next = new;
    list->len++;
}
