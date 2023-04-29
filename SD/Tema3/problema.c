#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void* data;
    struct Node* next;
} Node;

typedef struct TList {
    Node* head;
    int len;
} TList;

void init(TList **list);                        //done
int add(TList *list, int n, void* data);        //done
void* nodeRemove(TList *list, int n);           //done
int length(TList *list);                        //done
void print_int_list(TList *list);               //done
void print_string_list(TList *list);            //done
void free_list(TList **list);                   //done

void* findMiddle(TList *list);                  //done


int main() {
    TList *list;
    init(&list);

    int v[] = {1, 2, 3, 4, 5, 6, 7, 8}, i;
    for(i = 0; i < 8; i++)
        add(list, i, &v[7 - i]);

    nodeRemove(list, 3);
    nodeRemove(list, 0);
    print_int_list(list);
    print_string_list(list);
    free_list(&list);

    return 0;
}

void init(TList **list) {
    (*list)->len = 1;
    *list = (TList*) calloc(1, sizeof(TList));
}

int add(TList *list, int n, void* data) {

    list->len++;
    if(!n) {
        Node* new = (Node*) malloc(sizeof(Node*));
        new->data = data;
        new->next = list->head;
        list->head = new;

    } else if(n <= list->len) {
                Node *p = list->head, *new = (Node*) malloc(sizeof(Node*));
                int i;
                for(i = 0; i < n - 1; i++) p = p->next;
                new->data = data;
                new->next = p->next;
                p->next = new;
           }
}

void* nodeRemove(TList *list, int n) {

    void* ans;
    Node *p = list->head;
    list->len--;
    if(!n) {
        ans = list->head->data;
        list->head = list->head->next;
        free(p);

    } else if(n <= list->len) {
                Node *q;
                int i;
                for(i = 0; i < n - 1; i++) p = p->next;
                q = p->next;
                ans = q->data;
                p->next = q->next;
                free(q);
           }
    return ans;
}

int length(TList *list) { return list->len; }

void print_int_list(TList *list) {

    Node *curr = list->head;
    int i;
    for(i = 0; i < list->len; i++) {
         printf("%d ", *(int*) curr->data);
         curr = curr->next;
    }
    printf("\n");
}

void print_string_list(TList *list) {

    Node *curr = list->head;
    int i;
    for(i = 0; i < list->len; i++) {
         printf("%c ", *(char*) curr->data);
         curr = curr->next;
    }
    printf("\n");
}

void free_list(TList **list) {

    int i, j;
    Node *p;
    for(i = 0; i < (*list)->len; i++) {
        p = (*list)->head;
        for(j = 0; j < (*list)->len; j++) p = p->next;
        free(p);
        (*list)->len--;
    }
    free(*list);
}

void* findMiddle(TList *list) {

    int n = list->len / 2 + (list->len % 2), i;
    Node *p;
    for(i = 0; i < n; i++) p = p->next;
    return p->data;
}