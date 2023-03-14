#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

int isListEmpty(Node* head);
void push(Node** head, int value);
int pop(Node** head);
void displayList(Node* head);
void sortList(Node** head, int size);

int main() {

    Node* head = NULL;

    printf("%d\n", isListEmpty(head));
    for(int i = 0; i < 10; i++) push(&head, i + 1);
    displayList(head);
    printf("\n");
    sortList(&head, 10);
    displayList(head);
    printf("\n%d", isListEmpty(head));
    for(int i = 0; i < 10; i++) pop(&head); //free the memory
    printf("\n%d\n", isListEmpty(head));


    return 0;
}

int isListEmpty(Node* head) {
    return (head == NULL);
}

void push(Node** head, int value) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = value;
    new->next = (*head);
    (*head) = new;
}

int pop(Node** head) {
    Node* p = (*head);
    int ans;
    ans = (*head)->data;
    (*head) = (*head)->next;
    free(p);
    return ans;
}

void displayList(Node* head) {
    Node* current = head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

void sortList(Node** head, int size) {
    Node* current, *before;
    short isSorted = 0;

    while(!isSorted) { //bubbleSort
        isSorted = 1;
        before = (*head);
        current = (*head)->next;
        for(int i = 0; i < size - 1; i++) {
            if(before->data > current->data) { //swap
                before->data ^= current->data;
                current->data ^= before->data;
                before->data ^= current->data;
                isSorted = 0;
            }
            before = before->next;
            current = current->next;
        }
    }
}
