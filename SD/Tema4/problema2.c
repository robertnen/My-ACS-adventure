#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void * data;
    struct node *next, *prev;
} node;

typedef struct TDoubleLinkedList {
    node *head;
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
    // print_reversedInt(list);
    // print_reversedString(list);
    removeNode(list, 2);
    printInt(list);
    add_in_order(list, &v[4]);
    printInt(list);

    node *p = list->head->next, *q;

    for(int i = 1; i <= list->len; i++) {
        q = p->next;
        for(int j = i + 1; j <= list->len; j++)
            if(*(int*)p->data == *(int*)q->data)
                removeNode(list, j);
        p = p->next;
    }
    printInt(list);
    freeList(list);
    return 0;
}

List* init() {
    List *list = (List*) calloc(1, sizeof(List));
    list->head = (node*) calloc(1, sizeof(node));
    list->head->next = list->head;
    list->head->prev = list->head;
    return list;
}

void freeList(List* list) {
    node *p = list->head->prev, *q;
    int pos = list->len;
    while(pos--) {
        q = p;
        p = p->prev;
        free(q);
    }
    free(list->head);
    free(list);
}

void add(List* list, int pos, void* data) {
    node *new = calloc(1, sizeof(node)), *p;
    new->data = data;
    list->len++;
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

void removeNode(List* list, int pos) {
    node *p = list->head, *q;
    while(pos-- > 1) p = p->next;
    q = p->next;
    p->next = q->next;
    q->next->prev = p;
    free(q);
    list->len--;
}

void printInt(List* list) {
    node *p = list->head->next;
    int pos = list->len;
    while(pos--) {
        printf("%d ", *(int*)p->data);
        p = p->next;
    }
    printf("\n");
}

void printString(List* list) {
    node *p = list->head->next;
    int pos = list->len;
    while(pos--) {
        printf("%c ", *(char*)p->data);
        p = p->next;
    }
    printf("\n");
}

void print_reversedInt(List *list) {
    node *p = list->head->prev;
    int pos = list->len;
    while(pos--) {
        printf("%d ", *(int*)p->data);
        p = p->prev;
    }
    printf("\n");
}

void print_reversedString(List *list) {
    node *p = list->head->prev;
    int pos = list->len;
    while(pos--) {
        printf("%c ", *(char*)p->data);
        p = p->prev;
    }
    printf("\n");
}

void add_in_order(List *list, void* data) {
    node *new = (node*) calloc(1, sizeof(node)), *p;
    int pos = list->len;
    new->data = data;
    p = list->head->next;
    while(*(int*)p->data < *(int*)data && pos++ < list->len) p = p->next;
    p = p->next;
    new->next = p->next;
    new->prev = p;
    p->next->prev = new;
    p->next = new;
    list->len++;
}
