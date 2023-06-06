#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char key[50];
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[10];
} HashTable;

int hash(char* key) {
    int sum = 0;
    for(int i = 0; i < strlen(key); i++) sum += key[i];
    return sum % 10;
}

void initHashTable(HashTable* hashtable) {
    for(int i = 0; i < 10; i++) hashtable->buckets[i] = NULL;
}

void insertKey(HashTable* hashtable, char* key) {
    int aux = hash(key);
    Node* newNode = (Node*) calloc(1, sizeof(Node)), *p;
    strcpy(newNode->key, key);

    if(!hashtable->buckets[aux]) hashtable->buckets[aux] = newNode;
    else {
        p = hashtable->buckets[aux];
        while(p->next) p = p->next;
        p->next = newNode;
    }
}

int searchKey(HashTable* hashtable, char* key) {
    int aux = hash(key);
    Node* p = hashtable->buckets[aux];
    while(p) {
        if(!strcmp(p->key, key)) return 1;
        p = p->next;
    }
    return 0;
}

void deleteKey(HashTable* hashtable, char* key) {
    int aux = hash(key);
    Node* p = hashtable->buckets[aux], *prev = NULL;
    while(p) {
        if(!strcmp(p->key, key)) {
            if(!prev) hashtable->buckets[aux] = p->next;
            else prev->next = p->next;
            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }
}

void showHashTable(HashTable* hashtable) {
    for(int i = 0; i < 10; i++) {
        printf("Galeata %d: ", i);
        Node* p = hashtable->buckets[i];
        while(p) {
            printf("%s ---> ", p->key);
            p = p->next;
        }
        printf("\\0\n");
    }
}

int main() {
    HashTable hashtable;
    initHashTable(&hashtable);

    insertKey(&hashtable, "audi");
    insertKey(&hashtable, "bmw");
    insertKey(&hashtable, "dacia papuc");
    insertKey(&hashtable, "mercedes");
    insertKey(&hashtable, "nissan");
    insertKey(&hashtable, "lotus");

    showHashTable(&hashtable);

    printf("\nExista 'lotus': %s\n", searchKey(&hashtable, "lotus") ? "Da\n" : "Nu\n");
    printf("Exista 'opel': %s\n", searchKey(&hashtable, "opel") ? "Da\n" : "Nu\n");

    deleteKey(&hashtable, "lotus");
    deleteKey(&hashtable, "bmw");

    showHashTable(&hashtable);

    return 0;
}