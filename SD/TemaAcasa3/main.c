/* NENCIU George-Robert - 313CC */
#include "essentials.h"

int main(int argc, char const *argv[]) {

    #ifdef DEBUG // debug e pentru mine ca sa vad cum functioneaza programul
        FILE *sendLog = fopen("log.txt", "w");
        if(!sendLog) sendErrorOfFileNull("log.txt", "FILE*", "main");

        fprintf(sendLog, "This file contains what the important variables ");
        fprintf(sendLog, "contain.\nargc = %d\n", argc);
        int index;
        for(index = 0; index < argc; index++)
            fprintf(sendLog, "argv[%d] = |%s|\n", index, argv[index]);
        fprintf(sendLog, "\n");
    #endif

    //verific daca numarul de argumente este 2
    if(argc != 2) {
        fprintf(stderr, "Number of arguments is not 2. It is %d. To use", argc);
        fprintf(stderr, "this program you need to have the following format:");
        fprintf(stderr, "\n./nameOfExe N , where N is '1' or '2'.\nTry again!\n");
        fprintf(stderr, "Number of arguments you've entered: %d\n", argc);
        return 0;
    }

    //verific daca al doilea argument e ce trebuie
    if(argv[1][0] != '1' && argv[1][0] != '2') {
        fprintf(stderr, "Second argument should be '1' or '2'. You've entered '%c'.", argv[1][0]);
        fprintf(stderr, "\nFor this program you need to have the following format:");
        fprintf(stderr, "\n./nameOfExe N , where N is '1' or '2'.\nTry again!\n");
        return 0;
    }

    FILE *src = fopen("tema3.in", "r"), *dest = fopen("tema3.out", "w");
    if(!src) sendErrorOfFileNull("tema3.in", "FILE*", "main");

    char lineFile[100], names[2][100];
    int n, m, i, j, pos, pos1, pos2, cost, *costs, *sum;
    int *isVisited, *queue, st, dr, counter, area, aux, id;
    Graph g;

    fgets(lineFile, 100, src);
    lineFile[strlen(lineFile) - 2] = '\0';

    n = charToNum(lineFile);

    //inainte linie era de forma N_M si raman cu M
    memmove(lineFile, lineFile + getPosOfSpace(lineFile), strlen(lineFile));
    m = charToNum(lineFile);

    //initializez ce am nevoie
    g.size = 0;
    g.adjLists = (Node**) calloc(n, sizeof(Node*));
    if(!g.adjLists) sendErrorOfNull("g.adjLists", "Node**", "main");

    g.areas = (int*) calloc(n, sizeof(int));
    if(!g.areas) sendErrorOfNull("g.areas", "int*", "main");

    g.names = (char**) calloc(n, sizeof(char*));
    if(!g.names) sendErrorOfNull("g.name", "char**", "main");

    g.nodes = (int*) calloc(n, sizeof(int));
    if(!g.nodes) sendErrorOfNull("g.nodes", "int*", "main");

    g.depths = (int*) calloc(n, sizeof(int));
    if(!g.depths) sendErrorOfNull("g.depths", "int*", "main");

    for(i = 0; i < n; i++) {
        g.adjLists[i] = (Node*) calloc(1, sizeof(Node));
        if(!g.adjLists[i]) sendErrorOfNull("g.adjLists[undef]", "Node*", "main");

        g.names[i] = (char*) calloc(50, sizeof(char));
        if(!g.names[i]) sendErrorOfNull("g.name[undef]", "char*", "main");

        g.adjLists[i]->cost = 0; //costul de la un nod la el insusi e 0
        g.adjLists[i]->id = i; //fiecare nod e vecin cu el insusi
        g.adjLists[i]->edgeCounter = 0; //initialez
    }

    for(i = 0; i < m; i++) { // fiecare linie e de forma NUME1_NUME2_NR
        fgets(lineFile, 100, src);
        lineFile[strlen(lineFile) - 2] = '\0';

        pos = getPosOfSpace(lineFile);
        strncpy(names[0], lineFile, pos - 1);
        names[0][pos - 1] = '\0';
        memmove(lineFile, lineFile + pos, strlen(lineFile)); // am NUME2_NR

        pos = getPosOfSpace(lineFile);
        strncpy(names[1], lineFile, pos - 1);
        names[1][pos - 1] = '\0';
        strcpy(lineFile, lineFile + pos); // am ramas cu NR

        cost = charToNum(lineFile);
        pos1 = findPosOfName(g, names[0]); //verific daca exista deja locatia
        pos2 = findPosOfName(g, names[1]); //si aici la fel

        if(pos1 == -1) {
            pos1 = g.size++; //am o locatie noua
            strcpy(g.names[pos1], names[0]);
        }

        if(pos2 == -1) {
            pos2 = g.size++; //am o locatie noua
            strcpy(g.names[pos2], names[1]);
        }

        #ifdef DEBUG
            fprintf(sendLog, "\\/\\/\\/\\/\\/\\/\\/\\/\\/\n");
            fprintf(sendLog, "pos1 = %d\npos2 = %d\n", pos1, pos2);
        #endif

        g.adjLists[pos1] = createNode(g.adjLists[pos1], pos2); //adaug arc
        pos = findPosOfNode(g.adjLists[pos1], pos2);
        getAdress(g, pos1, pos)->cost = cost;

        if(argv[1][0] == '1') { //daca cerinta e 1, e graf neorientat
            g.adjLists[pos2] = createNode(g.adjLists[pos2], pos1);
            pos = findPosOfNode(g.adjLists[pos2], pos1);
            getAdress(g, pos2, pos)->cost = cost;
        }
    }

    isVisited = (int*) calloc(n, sizeof(int));
    if(!isVisited) sendErrorOfNull("isVisited", "int*", "main");

    costs = (int*) calloc(n, sizeof(int));
    if(!costs) sendErrorOfNull("costs", "int*", "main");

    //cerinta 1
    if(argv[1][0] == '1') {

        queue = (int*) calloc(n, sizeof(int));
        if(!queue) sendErrorOfNull("queue", "int*", "main");

        counter = area = 0;
        while(counter - n) { // cat timp nu am trecut prin toate nodurile
            area++;
            for(i = 0; isVisited[i]; i++);

            st = dr = 0;
            isVisited[i] = 1;
            queue[dr++] = i;
            counter++;
            g.areas[i] = area;
            g.nodes[area]++;

            while(st < dr) { //fac BFS fara a folosi functia deoarece am nev
                aux = queue[st++]; // si de alte date si e modificat
                for(i = 0; i < g.adjLists[aux]->edgeCounter; i++) {
                        id = getAdress(g, aux, i)->id;
                        if(!isVisited[id]) {
                            isVisited[id] = 1;
                            queue[dr++] = id;
                            counter++;
                            g.areas[id] = area;
                            g.nodes[area]++;
                        }
                }
            }
        }

        sum = (int*) calloc(n, sizeof(int));
        if(!sum) sendErrorOfNull("sum", "int*", "main");

        for(i = 0; i < n; i++) { //resetez ca sa pot folosi Prim
            costs[i] = infinity;
            isVisited[i] = 0;
        }

        pos1 = counter = 0; //counter e pt suma
        while(pos1++ < area) {
            for(i = 0; g.areas[i] != pos1; i++);
            aux = i;

            free(queue); //in coada voi baga fiecare componenta
            queue = (int*) calloc(n, sizeof(int));
            if(!queue) sendErrorOfNull("queue", "int*", "main");

            queue = BFS(g, i, isVisited, queue); //bag o componenta in coada

            #ifdef DEBUG
                fprintf(sendLog, "\nQueue for area %d:\n", pos1);
                for(i = 0; i < g.nodes[pos1]; i++) fprintf(sendLog, "queue[%d] = %d\n", i, queue[i]);
            #endif

            pos2 = g.nodes[pos1]; //tin minte cate noduri are zona
            costs[aux] = 0; //aux a ramas primul nod nefolosit

            free(isVisited); //reinitializez
            isVisited = (int*) calloc(n, sizeof(int));
            if(!isVisited) sendErrorOfNull("isVisited", "int*", "main");

            for(i = 0; i < pos2 - 1; i++) {
                cost = infinity;
                for(j = 0; j < pos2; j++)
                    if(!isVisited[queue[j]] && costs[queue[j]] < cost) {
                        cost = costs[queue[j]];
                        pos = j; //aici tin minte unde ar trb sa merg mai departe
                    }

                isVisited[queue[pos]] = 1;
                for(j = 0; j < pos2; j++) {
                    if(isVisited[queue[j]]) continue;
                    if(findPosOfNode(g.adjLists[queue[pos]], queue[j]) == -1) continue;

                    cost = getAdress(g, queue[pos], findPosOfNode(g.adjLists[queue[pos]], queue[j]))->cost;
                    if(cost < costs[queue[j]]) costs[queue[j]] = cost;

                }
            }
            for(i = 0; i < pos2; i++) sum[counter] += costs[queue[i]];
            counter++;
        }
        qsort(sum, counter, sizeof(int), cmpQSort); //sortare
        fprintf(dest, "%d\n", counter); //numarul de zone
        for(i = 0; i < counter; i++) fprintf(dest, "%d\n", sum[i]); //costurile

        #ifdef DEBUG
            Node *p;
            fprintf(sendLog, "\nGraph has the following nodes and edges:\n");
            for(i = 0; i < g.size; i++) {
                fprintf(sendLog, "Node id + name + area: %d |%s| %d\n", i, g.names[i], g.areas[i]);
                p = g.adjLists[i];
                for(j = 0; j < g.adjLists[i]->edgeCounter; j++) {
                    p = p->next;
                    fprintf(sendLog, "---> %d or |%s| (cost = %d area = %d)\n", p->id, g.names[p->id], p->cost, g.areas[p->id]);
                }
                fprintf(sendLog, "Number of neighbors: %d\n", g.adjLists[i]->edgeCounter);
                fprintf(sendLog, "++++++++++++++++++++++++++++++++++++++++++\n\n");
            }

            fprintf(sendLog, "Number of components: %d\n", area);
            fprintf(sendLog, "Number of nodes / component:\n");
            for(i = 0; i < area; i++)
                fprintf(sendLog, "===> %d are %d noduri\n", i + 1, g.nodes[i + 1]);
            fprintf(sendLog, "-----------------------------------\n");
            fprintf(sendLog, "\nDistance without matrix:\n");
            for(i = 0; i < n; i++) {
                for(j = 0; j < g.adjLists[i]->edgeCounter; j++) {
                    p = getAdress(g, i, j);
                    fprintf(sendLog, "%d~(%d) ", p->id, p->cost);
                }
            fprintf(sendLog, "\n");
            }
        #endif

        free(queue);
        free(sum);

    } else { //cerinta 2
        for(i = 0; i < n; i++) { //citesc ce mai am de citit
            fgets(lineFile, 100, src);
            lineFile[strlen(lineFile) - 2] = '\0';

            strncpy(names[0], lineFile, getPosOfSpace(lineFile) - 1);
            names[0][getPosOfSpace(lineFile) - 1] = '\0';

            strcpy(lineFile, lineFile + getPosOfSpace(lineFile));

            g.depths[findPosOfName(g, names[0])] = charToNum(lineFile);
            #ifdef DEBUG
                fprintf(sendLog, "name = |%s|\n depth = %d\n", names[0], cost);
            #endif
        }

        int total, dist1, dist2, isValid = 1, *path, maxim = infinity;
        char output[2000] = ""; //output va avea traseul cerut
        fgets(lineFile, 100, src);
        lineFile[strlen(lineFile) - 2] = '\0';
        total = charToNum(lineFile); //comoara

        #ifdef DEBUG
            Node *p;
            fprintf(sendLog, "treasure = %d\n", total);
            fprintf(sendLog, "\nGraph has the following nodes and edges:\n");
            for(i = 0; i < g.size; i++) {
                fprintf(sendLog, "Node id + name + depth + area: %d |%s| %d %d\n", i, g.names[i], g.depths[i], g.areas[i]);
                p = g.adjLists[i];
                for(j = 0; j < g.adjLists[i]->edgeCounter; j++) {
                    p = p->next;
                    fprintf(sendLog, "---> %d or |%s| (cost = %d depth = %d area = %d)\n", p->id, g.names[p->id], p->cost, g.depths[p->id], g.areas[p->id]);
                }
                fprintf(sendLog, "Number of neighbors: %d\n", g.adjLists[i]->edgeCounter);
                fprintf(sendLog, "++++++++++++++++++++++++++++++++++++++++++\n\n");
            }

            fprintf(sendLog, "\nDistance without matrix:\n");
            for(i = 0; i < n; i++) {
                for(j = 0; j < g.adjLists[i]->edgeCounter; j++) {
                    p = getAdress(g, i, j);
                    fprintf(sendLog, "%d~(%d) ", p->id, p->cost);
                }
            fprintf(sendLog, "\n");
            }
        #endif

        pos1 = findPosOfName(g, "Corabie"); //nodul unde e "Corabia"
        pos2 = findPosOfName(g, "Insula"); //nodul unde e "Insula"

        path = shortestPathWithDijkstra(g, findPosOfName(g, "Corabie"), costs, isVisited);
        dist1 = costs[pos2]; //am costul pana la "Insula"

        free(path); //vreau sa reinitializez ca nu imi trebuie arborele
        free(isVisited); //aici am nevoie sa vad daca am vizitat
        isVisited = (int*) calloc(n, sizeof(int));
        if(!isVisited) sendErrorOfNull("isVisited", "int*", "main");

        free(costs); //imi trebuie alte costuri
        costs = (int*) calloc(n, sizeof(int));
        if(!costs) sendErrorOfNull("costs", "int*", "main");

        path = shortestPathWithDijkstra(g, findPosOfName(g, "Insula"), costs, isVisited);
        dist2 = costs[pos1]; //am costul pana la "Corabie"

        if(dist1 == infinity) { //nu exista drum
            fprintf(dest, "Echipajul nu poate ajunge la insula\n");
            isValid = 0; //ca sa nu afisez ceva in plus
        }

        if(dist2 == infinity) { //nu exista drum
            fprintf(dest, "Echipajul nu poate transporta comoara inapoi la corabie\n");
            isValid = 0; //ca sa nu afisez ceva in plus
        }

        if(isValid) { //exista drum si afisez ce mi se cere
            showRoad(path, findPosOfName(g, "Corabie"), g, &maxim, output);
            fprintf(dest, "%s\n%d\n%d\n%d\n", output, dist2, maxim, total / maxim);
        }

        free(path);
    }

    free(isVisited); //eliberarea memoriei
    free(costs);

    for(i = 0; i < g.size; i++) {
        for(j = g.adjLists[i]->edgeCounter; j >= 0; j--)
            free(getAdress(g, i, j));
        free(g.adjLists[i]);
    }
    free(g.areas);
    free(g.nodes);
    free(g.depths);
    free(g.adjLists);

    for(i = 0; i < g.size; i++) free(g.names[i]);
    free(g.names);

    #ifdef DEBUG
        fclose(sendLog);
    #endif
    fclose(src);
    fclose(dest);
    return 0;
}