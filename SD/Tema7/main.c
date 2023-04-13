#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Treap {
    int key, priority;
    struct Treap *left ,*right;
} Treap;

typedef struct Trie {
    int count, nrfii;
    struct Trie* child[26];
} Trie;

Trie* initTrie() {
    Trie *p = (Trie*) calloc(1, sizeof(Trie));
    p->count = 1;
    for(int i = 0; i < 26; i++) p->child[i] = NULL;
    return p;
}

void insertTrie(Trie *t, char *str) {
    int len = strlen(str);
    Trie *p = t;
    for(int i = 0; i < len; i++) {
        if(p->child[(int)(str[i] - 'a')] == NULL) p->child[(int)(str[i] - 'a')] = initTrie();
        p = p->child[(int)(str[i] - 'a')];
    }
    p->count = 0;
}

int searchTrie(Trie *t, char *str) {
    int len = strlen(str);
    Trie *p = t;
    for(int i = 0; i < len; i++) {
        if(p->child[(int)(str[i] - 'a')] == NULL) return 0;
        p = p->child[(int)(str[i] - 'a')];
    }
    return !p->count;
}

int isLeaf(Trie *t, char *str) {
    Trie *aux = t;
    for(int i = 0; str[i]; i++)
        if(aux->child[(int)(str[i] - 'a')]) aux = aux->child[(int)(str[i] - 'a')];
    return !aux->count;
}

char* longestPrefix(Trie* t, char* str) {
    if(!str || str[0] == '\0') return NULL;
    int len = strlen(str);
    char *aux = (char*) calloc(len + 1, sizeof(char));
    Trie *tmp = t;
    strcpy(aux, str);

    int pos;
    if(!len) pos = 0;
    else {
        for(int i = 0; i < len; i++)
            if(tmp->child[(int)(str[i] - 'a')]) {
                for(int j = 0; j < 26; j++)
                    if(j != (int)(str[i] - 'a') && tmp->child[j]) {
                        pos = i + 1;
                        break;
                    }
                tmp = tmp->child[(int)(str[i] - 'a')];
            }
    }

    if(pos >= 0) {
        aux[pos] = '\0';
        aux = (char*) realloc(aux, (pos + 1) * sizeof(char));
    }

    return aux;
}

void freeNode(Trie *t) {
    for(int i = 0; i < 26; i++)
        if(t->child[i]) freeNode(t->child[i]);
    free(t);
}

Trie* deleteNode(Trie *t, char *str) {
    if(!t) return NULL;
    if(!str || str[0] == '\0') return t;
    if(!isLeaf(t, str)) return t;
    Trie *tmp = t;
    char *aux = longestPrefix(t, str);
    if(aux[0] == '\0') {
        free(aux);
        return t;
    }

    int i;
    for(i = 0; aux[i] != '\0'; i++) {
        if(tmp->child[(int)(aux[i] - 'a')]) tmp = tmp->child[(int)(aux[i] - 'a')];
        else {
            free(aux);
            return t;
        }
    }
    int len = strlen(str);
    while(i < len) {
        if(tmp->child[(int)(str[i] - 'a')]) {
            Trie *tmp2 = tmp->child[(int)(str[i] - 'a')];
            tmp->child[(int)(str[i] - 'a')] = NULL;
            freeNode(tmp2);
        }
        i++;
    }
    free(aux);
    return t;
}

void freeTrie(Trie *t, char **str, int size) {
    for(int i = 0; i < size; i++) deleteNode(t, str[i]);
    free(t);
    t = NULL;
}

void printNode(Trie *t, int n, char *str, char *toPrint) {
    if(!t) return;
    if(!t->count) {
        printf("%s", toPrint);
        for(int i = 0; i < n; i++) printf("%c", str[i]);
        printf("\n");
    }

    for(int i = 0; i < 26; i++)
        if(t->child[i]) {
            str[n] = (char)(i + 'a');
            printNode(t->child[i], n + 1, str, toPrint);
        }
}

void printTrie(Trie *t, char *str, int size) {
    Trie *tmp = t;
    int pos = 0, len = 0;
    char aux[100], aux2[100];
    tmp = t;
    for(int i = 0; i < size; i++) {
        if(tmp->child[(int)(str[i] - 'a')]) {
            tmp = tmp->child[(int)(str[i] - 'a')];
            aux2[len++] = str[i];
        } else {
            printf("Nu exista!\n");
            return;
        }
    }
    aux2[len] = '\0';
    printNode(tmp, pos, aux, aux2);
}

const int POWER_OF_TEN = 1000;

Treap* newNode(int key);
Treap* delete(Treap *t, int key);
void inorder(Treap *t);
Treap* insert(Treap *t, int key);
Treap* rotateLeft(Treap *z);
Treap* rotateRight(Treap *w);

int charToNum(char str[]) {
	int size = strlen(str);
	int n = 0, i;
	for(i = 0; i < size && str[i] != ' '; i++) n = n * 10 + str[i] - '0';
	return n;
}

int main() {

    // Treap *tree = NULL;
    // tree = insert(tree, 1);
    // tree = insert(tree, 3);
    // tree = insert(tree, 4);
    // tree = insert(tree, 2);
    // tree = insert(tree, 5);
    // tree = insert(tree, 7);
    // tree = insert(tree, 6);
    // tree = insert(tree, 9);
    // tree = insert(tree, 8);
    // inorder(tree);
    // printf("\n");
    // delete(tree, 4);
    // inorder(tree);

    // char *keys[10] = {"abcd", "dasg", "aaabc", "casd", "dashasdasd", "abcca", "casfafa"};
    // char test[] = "stasda";
    Trie *tree = initTrie();
    // for(int i = 0; i < 7; i++) insertTrie(tree, keys[i]);
    // printf("|%10s| isFound = %d\n", keys[0], searchTrie(tree, keys[0]));
    // printf("|%10s| isFound = %d\n", keys[1], searchTrie(tree, keys[1]));
    // printf("|%10s| isFound = %d\n", keys[2], searchTrie(tree, keys[2]));
    // printf("|%10s| isFound = %d\n", keys[3], searchTrie(tree, keys[3]));
    // printf("|%10s| isFound = %d\n", keys[4], searchTrie(tree, keys[4]));
    // printf("|%10s| isFound = %d\n", keys[5], searchTrie(tree, keys[5]));
    // printf("|%10s| isFound = %d\n", keys[6], searchTrie(tree, keys[6]));
    // printf("|%10s| isFound = %d\n", test, searchTrie(tree, test));
    // printf("=======================================\n");
    // for(int i = 0; i < 7; i++) tree = deleteNode(tree, keys[i]);
    // printf("|%10s| isFound = %d\n", keys[0], searchTrie(tree, keys[0]));
    // printf("|%10s| isFound = %d\n", keys[1], searchTrie(tree, keys[1]));
    // printf("|%10s| isFound = %d\n", keys[2], searchTrie(tree, keys[2]));
    // printf("|%10s| isFound = %d\n", keys[3], searchTrie(tree, keys[3]));
    // printf("|%10s| isFound = %d\n", keys[4], searchTrie(tree, keys[4]));
    // printf("|%10s| isFound = %d\n", keys[5], searchTrie(tree, keys[5]));
    // printf("|%10s| isFound = %d\n", keys[6], searchTrie(tree, keys[6]));
    // printf("|%10s| isFound = %d\n", test, searchTrie(tree, test));

    int n, m, pos = 0;
    FILE *src = fopen("lab7.in", "r");
    char inputFile[100], aux[100];
    fgets(inputFile, 100, src);
    inputFile[strlen(inputFile) - 1] = '\0';

    while(inputFile[pos++] != ' ');
    pos--;
    strncpy(aux, inputFile, pos);
    aux[pos] = '\0';
    n = charToNum(aux);
    strcpy(inputFile, inputFile + pos + 1);
    m = charToNum(inputFile);

    for(int i = 0; i < n; i++) {
        fgets(inputFile, 100, src);
        inputFile[strlen(inputFile) - 1] = '\0';
        insertTrie(tree, inputFile);
    }

    for(int i = 0; i < m; i++) {
        fgets(inputFile, 100, src);
        inputFile[strlen(inputFile) - 1] = '\0';
        printf("Prefixul introdus: %s\n", inputFile);
        printf("Cuvintele gasite:\n");
        printTrie(tree, inputFile, strlen(inputFile));
        printf("========================================\n");
    }

    fclose(src);
    return 0;
}

Treap* newNode(int key) {
    Treap *aux = (Treap*) calloc(1, sizeof(Treap));
    aux->key = key;
    aux->priority = rand() % POWER_OF_TEN;
    return aux;
}

Treap* rotateRight(Treap *w) {
    Treap *z = w->left, *a = z->right;
    z->right = w;
    w->left = a;
    return z;
}

Treap* rotateLeft(Treap *z) {
    Treap *w = z->right, *a = w->left;
    w->left = z;
    z->right = a;
    return w;
}

Treap* insert(Treap *t, int key) {
    if(t == NULL) return newNode(key);
    if(t->key < key) {
        t->right = insert(t->right, key);
        if(t->right->priority > t->priority) t = rotateLeft(t);
    } else {
        t->left = insert(t->left, key);
        if(t->left->priority > t->priority) t = rotateRight(t);
    }
    return t;
}

Treap* delete(Treap *t, int key) {
    if(t == NULL) return t;
    if(key < t->key) t->left = delete(t->left, key);
    else if(key > t->key) t->right = delete(t->right, key);
    else if(t->left == NULL) {
        Treap *aux = t->right;
        free(t);
        t = aux;
    } else if(t->right == NULL) {
        Treap *aux = t->left;
        free(t);
        t = aux;
    } else if(t->left->priority < t->right->priority) {
        t = rotateLeft(t);
        t->left = delete(t->left, key);
    } else {
        t = rotateRight(t);
        t->right = delete(t->right, key);
    }
    return t;
}

void inorder(Treap *t) {
    if(t) {
        inorder(t->left);
        printf("key: %d | priority: %d\n", t->key, t->priority);
        inorder(t->right);
    }
}