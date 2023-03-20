/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

int main() {

    FILE *src;
    char inputFile[100];
    const char* COMMANDS[] = {"MOVE_LEFT", "MOVE_RIGHT", "MOVE_LEFT_CHAR",
                              "MOVE_RIGHT_CHAR", "WRITE", "INSERT_LEFT",
                              "INSERT_RIGHT", "SHOW_CURRENT", "SHOW",
                              "UNDO", "REDO", "EXECUTE"};

    src = fopen("tema1.in", "r");
    fgets(inputFile, 100, src);
    int length = strlen(inputFile) - 1, i, j, n = 0, pos;
    inputFile[length] = '\0';

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

        printf("|%s| %d\n", inputFile, pos);
        switch (pos) {
            case  1: //move_left
            case  2: //move_right
            case  3: //move_left_char
            case  4: //move_right_char
                addQueue(queueExec, inputFile);
                break;
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
            case 11: //redo
            case 12: //execute
                break;
        }
    }
    freeQueue(queueExec);
    if(stackUndo) freeStack(stackUndo);
    if(stackRedo) freeStack(stackRedo);
    freeList(list);
    fclose(src);
    return 0;
}