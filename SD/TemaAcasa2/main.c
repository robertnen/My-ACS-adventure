/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treeFunc.h"

int main(int argc, char const *argv[]) {

    int n, i, treeSize, size1 = 0, size2 = 0;
    char inputFile[1000];
    unsigned char type;
    FILE *src, *dest;
    QuadTree *aux;
    Pixel **grid;
    Queue *queue;

    src = fopen(argv[argc - 2], "rb");
    if(!src) sendErrorOfFileNull(argv[argc - 2], "FILE*", "main");

    if(argc >= 5) { //cerinta 1 sau cerinta 2

        //citirea normala
        fgets(inputFile, 1000, src); //P6
        fgets(inputFile, 1000, src); // n x n
        inputFile[strlen(inputFile) - 1] = '\0';
        n = charToNum(inputFile);
        fgets(inputFile, 1000, src); // 255

        //citirea binara
        grid = (Pixel**) calloc(n, sizeof(Pixel*));
        if(!grid) sendErrorOfNull("grid", "Pixel**", "main");

        for(i = 0; i < n; i++) {
            grid[i] = (Pixel*) calloc(n, sizeof(Pixel));
            if(!grid[i]) sendErrorOfNull("grid[i]", "Pixel*", "main");
            fread(grid[i], sizeof(Pixel), n, src);
        }

        QuadTree *qTree = initQuadTree();
        int counter = 0, height = 0, size = 0;
        treeSize = 1;

        strcpy(inputFile, argv[2]);

        generateTree(qTree, grid, n, 0, 0, charToNum(inputFile), &counter, &treeSize);
        height = quadTreeHeight(qTree, 1);
        size = quadMaxSize(qTree, n);

        //folosesc coada oricum pentru eliberarea memoriei mai tarziu
        queue = (Queue*) calloc(treeSize, sizeof(Queue));
        if(!queue) sendErrorOfNull("queue", "Queue*", "main");

        BFS(qTree, queue);

        if(argv[1][2] == '1') { //cerinta 1

            dest = fopen(argv[argc - 1], "w");
            if(!dest) sendErrorOfFileNull(argv[argc - 1], "FILE*", "main");
            fprintf(dest, "%d\n%d\n%d\n", height, counter, size);

        } else {//cerinta 2
            dest = fopen(argv[argc - 1], "wb");
            if(!dest) sendErrorOfFileNull(argv[argc - 1], "FILE*", "main");
            fwrite(&n, 1, sizeof(int), dest);

            if(treeSize == 1) qTree->type = 1; //am pus tipul 0 si e un bloc

            for(i = 0; i < treeSize; i++)
                if(!queue[i].node->type) fwrite(&queue[i].node->type, 1, 1, dest);
                else {
                    fwrite(&queue[i].node->type, 1, 1, dest);
                    fwrite(&queue[i].node->pixel, 1, sizeof(Pixel), dest);
                }
            }
    } else { //cerinta 3

        dest = fopen(argv[argc - 1], "wb");
        if(!dest) sendErrorOfFileNull(argv[argc - 1], "FILE*", "main");

        fread(&n, sizeof(int), 1, src); //dimensiunea

        QueueNode *queueTree = NULL, *queueParent = NULL;

        while(fread(&type, 1, 1, src) == 1) {   //citesc coada
            aux = newNode(type);
            queueTree = enqueueNode(queueTree, &size1, aux);
            if(aux->type) fread(&aux->pixel, sizeof(Pixel), 1, src);
            else queueParent = enqueueNode(queueParent, &size2, aux);
        }

        QuadTree *qTree = NULL;
        grid = (Pixel**) calloc(n, sizeof(Pixel*));
        if(!grid) sendErrorOfNull("grid", "Pixel**", "main");

        for(i = 0; i < n; i++) {
            grid[i] = (Pixel*) calloc(n, sizeof(Pixel));
            if(!grid[i]) sendErrorOfFileNull("grid[i]", "Pixel*", "main");
        }

        //imaginea are doar o culoare
        if(!size2) queueParent = enqueueNode(queueParent, &size2, aux);

        aux = frontQueue(queueParent);
        treeSize = size1;
        remakeQuadTree(qTree, &queueTree, &queueParent, &size1, &size2);
        qTree = aux;
        remakeImage(qTree, grid, n, 0, 0);

        //formez fisierul cu imaginea
        fprintf(dest, "P6\n%d %d\n255\n", n, n);
        for(i = 0; i < n; i++) fwrite(grid[i], n, sizeof(Pixel), dest);

        freeQueue(queueTree, &size1);
        freeQueue(queueParent, &size2);

        //folosesc coada oricum pentru eliberarea memoriei mai tarziu
        queue = (Queue*) calloc(treeSize, sizeof(Queue));
        BFS(qTree, queue);

    }

    //eliberarea memoriei
    for(i = treeSize - 1; i > -1; i--) free(queue[i].node);
    free(queue);

    //restul de memorie este eliberata
    for(i = 0; i < n; i++) free(grid[i]);
    free(grid);
    fclose(src);
    fclose(dest);
    return 0;
}