/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

int main() {

    FILE *src;
    char inputFile[100];
    const char* COMMANDS[] = {"MOVE_LEFT_CHAR", "MOVE_RIGHT_CHAR", "MOVE_LEFT",
                              "MOVE_RIGHT", "WRITE", "INSERT_LEFT",
                              "INSERT_RIGHT", "SHOW_CURRENT", "SHOW",
                              "UNDO", "REDO", "EXECUTE"};

    src = fopen("tema1.in", "r");
    fgets(inputFile, 100, src);
    int length = strlen(inputFile) - 1, i, j, n, pos, totalU, totalR;
    inputFile[length] = '\0';
    n = totalU = totalR = 0;

    for(i = 0; i < length; i++) n = n * 10 + inputFile[i] - '0';

    Queue *queueExec = initQueue();
    List *list = initLista();
    addNode(list, 1, '#');
    Node *finger = list->head->next;
    Stack *stackUndo = initStack(), *stackRedo = initStack();

    for(i = 0; i < n; i++) {
        fgets(inputFile, 100, src);
        inputFile[strlen(inputFile) - 1] = '\0';

        for(j = 0; j < 12; j++) //caut a cata comanda e din lista
            if(strstr(inputFile, COMMANDS[j])) { pos = j + 1; break; }

        printf("input = |%s| pos = %d\n", inputFile, pos);

        switch (pos) {
            case  3: //move_left
            case  4: //move_right
            case  1: //move_left_char
            case  2: //move_right_char
            case  5: //write
                addQueue(queueExec, inputFile);
                /*pass*/
                break;
            case  6: //insert_left
                insertLeftChar(list, finger, inputFile[12]);
                break;
            case  7: //insert_right
                insertRightChar(list, finger, inputFile[13]);
                break;
            case  8: //show_current
                showCurrent(finger);
                break;
            case  9: //show
                show(list, finger);
                break;
            case 10: //undo
                finger = undo(stackUndo, stackRedo, finger);
                break;
            case 11: //redo
                finger = redo(stackUndo, stackRedo, finger);
                break;
            case 12: //execute
                finger = execute(queueExec, finger, &stackUndo, &stackRedo, list, &totalU, &totalR);
                break;
        }
    }
    freeQueue(queueExec);
    if(totalU) freeStack(stackUndo, totalU);
    if(totalR) freeStack(stackRedo, totalR);
    freeList(list);
    fclose(src);
    return 0;
}