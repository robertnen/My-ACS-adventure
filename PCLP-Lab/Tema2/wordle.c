#include <menu.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkTerminal();                   //verific daca suporta culori
void startUp();                         //pornesc jocul
void delaySeconds(int seconds);         //programul asteapta cateva secunde
void intro();                           //intro pentru joc (dureaza ~5 secunde)
void infoMenu(int, int, char*[], int);  //afisez posibila optiune aleasa
void showCenterTop(WINDOW*, int, int, int, char*, chtype); //meniu in centru-sus
void showCenterBottom(WINDOW*, int, int, int, char*, chtype); //meniu in centru-jos
int gameMenu();                         //meniul jocului
int setTime();                          //daca vreau sa joc contra timp
void drawTable();                       //deseneaza tabla
void toLower(char text[]);              //vreau numai litere mici
int letterExists(int c, int pos, char word[]); //verific ce culoare va avea litera
int controlMenu();                      //meniul care apare cand apas :
void letters(char ch, chtype color);    //afisez in dreapta ce s-a folosit
int playGame();                         //Wordle!!

int main (int argc, char* argv[]) {

    int ch, option = 1, stage;
    short withTime = 0;

    startUp(); //deschid jocul
    intro();  //mic intro :)

    while(option != 2) { //2 e iesirea

        option = gameMenu();

        if(option == 1) withTime = setTime(); //default e 0, adica nelimitat
        else if(!option) {
                while(!(stage = playGame(withTime)));
                if(stage == 1) {
                    erase();
                    bkgd(COLOR_PAIR(8));
                    refresh(); //ca sa nu apara buguri in terminal
                    endwin();
                    return 0;
                }
            } else break;
    }
    delaySeconds(1); //outro
    endwin();
    return 0;
}

void checkTerminal() {
    if(!has_colors()) {
        //jocul nu poate fi jucat!!
        endwin();
        printf("Acest terminal nu suporta culori!\n");
        exit(1);
    }
}

void startUp() {

    initscr();
    noecho();
    curs_set(0);

    keypad(stdscr, TRUE);

    checkTerminal();

    start_color();
    init_color(COLOR_BLUE, 192, 192, 192);//argintiu in teorie, dar la mn e gri
    init_color(COLOR_MAGENTA, 211, 211, 211); // gri deschis
    init_color(COLOR_RED, 220, 20, 60);       //aparent o sa fie gri daca nu

    //declar aici fiecare pereche de culori
    init_pair(1, COLOR_BLACK, COLOR_GREEN);     //pozitie corecta
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);    //exista
    init_pair(3, COLOR_BLACK, COLOR_WHITE);     //pentru tabla
    init_pair(4, COLOR_WHITE, COLOR_BLUE);      //fereastra principala
    init_pair(5, COLOR_CYAN, COLOR_BLUE);       //Wordle!!
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);   //fereastra secundara
    init_pair(7, COLOR_RED, COLOR_BLUE);        //asta e pt meniu la autor
    init_pair(8, COLOR_WHITE, COLOR_BLACK);     //nu apare in cuvant
    init_pair(9, COLOR_GREEN, COLOR_BLUE);      //pentru alegerea modului

    bkgd(COLOR_PAIR(4));

    refresh();
}

void delaySeconds(int seconds) {

    unsigned int timeToGet = time(0) + seconds; //momentul asteptat
    while(time(0) < timeToGet);                 //verific daca am trecut
}

void intro() {

    raw(); //fara comenzi de trimit semnal

    wmove(stdscr, LINES / 2 - 3, COLS / 2 - 11);
    waddstr(stdscr, "Acest joc a fost facut");

    wmove(stdscr, LINES / 2 - 2, COLS / 2 - 14);
    waddstr(stdscr, "pentru cei care adora Wordle");

    refresh();
    delaySeconds(3);

    wmove(stdscr, LINES / 2 - 3, COLS / 2 - 11);
    waddstr(stdscr, "  Bine ai venit la    ");

    wmove(stdscr, LINES / 2 - 2, COLS / 2 - 14);
    waddstr(stdscr, "          WORDLE!           ");

    refresh();
    delaySeconds(2);
    werase(stdscr);
    refresh();
}

void infoMenu(int x, int y, char* options[], int whereAmI) {

    mvwprintw(stdscr, (y + 11) / 2 + 1, (x - 23) / 2 + 5, "                         ");
    mvwprintw(stdscr, (y + 11) / 2 + 1, (x - 23) / 2 + 5, "Alegi '%s'?", options[whereAmI]);
    wrefresh(stdscr);
}

void showCenterTop(WINDOW* window, int start_y, int start_x, int width, char* title, chtype color) {

    int length, x, y;
    getyx(window, y, x);

    if(start_y) y = start_y;
    if(start_x) x = start_x;

    length = strlen(title);
    x = start_x + (width - length) / 2;

    wattron(window, color);
    mvwprintw(window, y, x, "%s", title); // WORDLE!!
    wattroff(window, color);

    refresh();
}

void showCenterBottom(WINDOW* window, int start_y, int start_x, int width, char* name, chtype color) {

    int length, x, y;
    getyx(window, y, x);

    if(start_y) y = start_y;
    if(start_x) x = start_x;

    length = strlen(name);
    x = start_x + (width - length) / 2;
    y = getmaxy(window) - 2;

    wattron(window, color);
    wattron(window, A_UNDERLINE);
    mvwprintw(window, y, x, "%s", name); // Autorul
    wattroff(window, A_UNDERLINE);
    wattroff(window, color);

    refresh();
}

int gameMenu() {

    char* options[] = {"Joaca", "Timp", "Iesire"};
    int i, ch, size = 3;
    int x, y, whereAmI = 0; //default e "Joaca"
    short isChoosing = 0;
    ITEM** menuItems;
    MENU* mainMenu;
    WINDOW* menuWindow;
    const int WIDTH = 20;

    getmaxyx(stdscr, y, x);

    menuItems = (ITEM**) calloc(size + 1, sizeof(ITEM*));

    for(i = 0; i < size; i++) menuItems[i] = new_item(options[i], "");
    menuItems[size] = (ITEM*)NULL;

    mainMenu = new_menu((ITEM**)menuItems);

    menuWindow = newwin(11, WIDTH, (y - 13) / 2, (x - 19) / 2);

    keypad(stdscr, FALSE);
    keypad(menuWindow, TRUE);
    wbkgd(menuWindow, COLOR_PAIR(4));

    set_menu_win(mainMenu, menuWindow);
    set_menu_sub(mainMenu, derwin(menuWindow, 5, WIDTH - 2, 3, 1));

    set_menu_back(mainMenu, COLOR_PAIR(4));
    set_menu_mark(mainMenu, " -> ");

    box(menuWindow, 0, 0);

    //basic info
    showCenterTop(menuWindow, 1, 0, WIDTH, "Wordle!!", COLOR_PAIR(5));
    showCenterBottom(menuWindow, 0, 0, WIDTH, "Facut de N. Robert", COLOR_PAIR(6));

    //mai jos meniul si cum il folosesc
    post_menu(mainMenu);
    wrefresh(menuWindow);

    while(!isChoosing && (ch = wgetch(menuWindow))) {
        switch(ch) {

            case KEY_DOWN:
            case 's':
            case 'S':
                menu_driver(mainMenu, REQ_DOWN_ITEM);
                if(++whereAmI > 2) whereAmI = 2;
                infoMenu(x, y, options, whereAmI);
                break;

            case KEY_UP:
            case 'w':
            case 'W':
                menu_driver(mainMenu, REQ_UP_ITEM);
                if(--whereAmI < 0) whereAmI = 0;
                infoMenu(x, y, options, whereAmI);
                break;

            case 10:
                isChoosing = 1;
                break;

            default:
                mvwprintw(stdscr, (y + 11) / 2, (x - 23) / 2 - 15, "Foloseste 'KEY_DOWN/s/S', 'KEY_UP/w/W' sau 'ENTER'...");
                wrefresh(stdscr);
                break;
        }
    }

    unpost_menu(mainMenu);
    werase(menuWindow);
    werase(stdscr);
    refresh();
    delwin(menuWindow);

    for(i = 0; i <= size; i++) free(menuItems[i]);
    free_menu(mainMenu);
    free(menuItems);

    return whereAmI;
}

int setTime() { //aici aleg daca vreau sa joc contra timp

    wattron(stdscr, A_BOLD | A_BLINK);
    mvwprintw(stdscr, LINES / 2 - 2, COLS / 2 - 21, "Cu timp? (30 de secunde / cuvant) (y / n)");
    refresh();
    wattroff(stdscr, A_BOLD | A_BLINK);

    mvwprintw(stdscr, LINES / 2, COLS / 2 - 4, "Scrie:");

    int ch;

    wattron(stdscr, COLOR_PAIR(7));

    while((ch = getch()) && (ch != 'y') && (ch != 'Y') && (ch != 'n') && (ch != 'N')){

        mvwprintw(stdscr, LINES / 2, COLS / 2 + 3, "%c", ch);
        wrefresh(stdscr);
    }

    wattroff(stdscr, COLOR_PAIR(7));

    wattron(stdscr, COLOR_PAIR(9));
    mvwprintw(stdscr, LINES / 2, COLS / 2 + 3, "%c", 10);
    mvwprintw(stdscr, LINES / 2, COLS / 2 + 3, "%c", ch);
    refresh();
    delaySeconds(2);
    wattroff(stdscr, COLOR_PAIR(9));
    erase();
    refresh();

    if(ch == 'Y' || ch == 'y') return 1;
    else return 0;
}

void drawTable() {

    int i;
    erase();

    attron(COLOR_PAIR(5));
    mvprintw(0, 0, "%s", "Wordle!!"); // WORDLE!!
    attroff(COLOR_PAIR(5));

    wattron(stdscr, COLOR_PAIR(3));

    for(i = 6; i <= 22; i += 4) mvhline(i, COLS / 2 - 9, 0, 21);
    for(i = -9; i <= 11; i += 4) mvvline(2, COLS / 2 + i, 0, 25);

    mvhline(2, COLS / 2 - 9, 0, 21); //ca sa arate mai bn
    mvhline(26, COLS / 2 - 9, 0, 21);

    wattron(stdscr, A_ALTCHARSET);

    //colturile
    mvaddch(26, COLS / 2 + 11, 106);
    mvaddch(2, COLS / 2 + 11, 107);
    mvaddch(2, COLS / 2 - 9, 108);
    mvaddch(26, COLS / 2 - 9, 109);

    // //top & bottom
    for(i = -5; i <= 7; i += 4) {

        mvaddch(2, COLS / 2 + i, 119);
        mvaddch(26, COLS / 2 + i, 118);
    }

    wattroff(stdscr, A_ALTCHARSET);
    wattroff(stdscr, COLOR_PAIR(3));

    //vreau sa am in stanga ce litere nu au fost incercate
    const char QWERTY[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                              'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                                 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

    for(i = 0; i < 10; i++) mvaddch(LINES / 2 - 4, 3 * i + 5, QWERTY[i]);
    for(i = 10; i < 19; i++) mvaddch(LINES / 2 - 1, 3 * (i - 10) + 6, QWERTY[i]);
    for(i = 19; i < 26; i++) mvaddch(LINES / 2 + 2, 3 * (i - 19) + 9, QWERTY[i]);

    wattron(stdscr, A_ALTCHARSET);
    for(i = 0; i < 10; i++) mvaddch(LINES / 2 - 3, 3 * i + 5, 97);
    for(i = 10; i < 19; i++) mvaddch(LINES / 2, 3 * (i - 10) + 6, 97);
    for(i = 19; i < 26; i++) mvaddch(LINES / 2 + 3, 3 * (i - 19) + 9, 97);
    wattroff(stdscr, A_ALTCHARSET);

    mvprintw(LINES / 2 - 4, COLS / 2 + 21, "Cuvant:");

    for(i = 0; i < 5; i++)
        mvaddch(LINES / 2 - 2, COLS / 2 + 20 + 2 * i, 97 | A_ALTCHARSET);
}

void toLower(char text[]) {

    int i;
    for(i = 0; i < strlen(text); i++)
        if('A' <= text[i] && text[i] <= 'Z')
            text[i] += 32;
}

int letterExists(int c, int pos, char word[]) {

    short isThere = 0, i;

    for(i = 0; i < strlen(word); i++) {

        if(c == word[i] && pos == i) return 2; //pozitie exacta
        if(c == word[i]) isThere = 1;          //exista litera in cuvant
    }

    return (isThere ? 1 : 0);
}

int controlMenu() {

    curs_set(0);
    erase();
    refresh();

    int ch, pos, i;
    char* options[] = {"Reincepe jocul", "Iesire"};
    MENU* menu;
    ITEM** items;
    keypad(stdscr, TRUE);

    items = (ITEM**) calloc(3, sizeof(ITEM*));

    for(i = 0; i < 2; i++) items[i] = new_item(options[i], "");
    items[2] = (ITEM*)NULL;

    menu = new_menu((ITEM**)items);
    post_menu(menu);
    set_menu_back(menu, COLOR_PAIR(4));
    set_menu_mark(menu, "*");
    refresh();

    while((ch = getch())) {
        switch(ch) {
            case KEY_DOWN:
                pos = 1;
                menu_driver(menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                pos = 0;
                menu_driver(menu, REQ_UP_ITEM);
                break;

            case 10:
                free_item(items[0]);
                free_item(items[1]);
                free(items);
                free_menu(menu);
                erase();
                refresh();
                return pos;
        }
    }
}

void letters(char ch, chtype color) {

    //vad in ce vector gasesc litera folosita
    char Q_1[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '\0'};
    char Q_2[] = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\0'};
    char Q_3[] = {'Z', 'X', 'C', 'V', 'B', 'N', 'M', '\0'};

    int which = 0, pos = 0, i;

    for(i = 0; i < strlen(Q_1); i++)
        if(Q_1[i] == ch) {
            which = 1;
            pos = i;
            break;
        }

    for(i = 0; i < strlen(Q_2); i++)
        if(Q_2[i] == ch) {
            which = 2;
            pos = i;
            break;
        }

    for(i = 0; i < strlen(Q_3); i++)
        if(Q_3[i] == ch) {
            which = 3;
            pos = i;
            break;
        }

    if(which == 1) mvaddch(LINES / 2 - 4, 3 * pos + 5, Q_1[pos] | color);
    else if(which == 2) mvaddch(LINES / 2 - 1, 3 * pos + 6, Q_2[pos] | color);
         else mvaddch(LINES / 2 + 2, 3 * pos + 9, Q_3[pos] | color);
}

int playGame(int withTime) {

    int ch, timeLeft, pos_x, pos_y, length = 0;
    int row = 1, col = 1, x, size = 0, i;
    short isOver = 0, isHalf = 0;
    char input[6], word[6];

    const char* WORDS[] = {"arici", "atent", "baiat",
                           "ceata", "debut", "peste",
                           "fixat", "hamac", "harta",
                           "jalon", "jucam", "lacat",
                           "magie", "nufar", "oaste",
                           "perus", "rigle", "roman",
                           "sanie", "scris", "sonda",
                           "texte", "tipar", "titan",
                           "zebra", "vapor", "vatra"};

    srand(time(0));
    strcpy(word, WORDS[rand() % 27]); //cuvantul care trebuie ghicit

    drawTable();

    pos_x = COLS / 2 + 20;
    pos_y = LINES / 2 - 2;
    x = COLS / 2 - 7;

    keypad(stdscr, TRUE);

    while(!isOver) {

        timeLeft = 30;

        if(withTime) halfdelay(10); //timp de asteptare
        while((ch = getch())) {

            curs_set(2);
            mvprintw(LINES / 2 + 5, COLS / 2 + 19, "                   ");
            mvprintw(LINES / 2 + 6, COLS / 2 + 21, "              "); //clean up
            move(pos_y, pos_x);
            refresh();
            if(length == 5) curs_set(0); //vizual
            if(ch == ERR && withTime) { //halfdelay e de vina
                mvprintw(LINES / 2 + 2, COLS / 2 + 22, "Timp: %2d", timeLeft--);
                if(timeLeft == -1) { //a trecut timpul
                    isOver = 1;
                    mvprintw(LINES / 2 + 3, COLS / 2 + 21, "Ai pierdut!");
                    mvprintw(LINES / 2 + 4, COLS / 2 + 18, "Cuvantul era %s!", word);
                    refresh();
                    delaySeconds(3);
                    erase();
                    refresh();
                    return 2;
                }
            } else
                if(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {

                        if(length == 5) { //deja am cuvant

                            mvprintw(LINES / 2 + 5, COLS / 2 + 19, "Un cuvant are maxim");
                            mvprintw(LINES / 2 + 6, COLS / 2 + 21, "5 caractere...");
                            curs_set(0);
                            refresh();

                        } else { //nu am cuvant inca
                            mvaddch(row * 4, x + (col - 1) * 4, ch);
                            mvaddch(pos_y, pos_x, ch);
                            refresh();
                            pos_x += 2;
                            length++;
                            input[size++] = ch;

                            if(col < 5) col++;
                        }
                } else
                    if(ch == 10 && length != 5) { //nu e de 5 litere

                            mvprintw(LINES / 2 + 5, COLS / 2 + 19, "Un cuvant are exact");
                            mvprintw(LINES / 2 + 6, COLS / 2 + 21, "5 caractere...");
                            refresh();
                    } else
                       if(ch == KEY_BACKSPACE && length > 0) { //sterg litera

                            pos_x -= 2;
                            if(col > 1) col--;
                            mvaddch(pos_y, pos_x, 97 | A_ALTCHARSET);
                            length--;
                            input[size--] = ' ';
                            for(i = 0; i <= 4; i++)
                                mvaddch(row * 4, x + i * 4, ' ');
                            for(i = 0; i < size; i++)
                                mvaddch(row * 4, x + i * 4, input[i]);
                            refresh();

                        } else
                            if(ch == 10) {

                                input[5] = '\0';
                                toLower(input);
                                if(!strcmp(input, word)) { //am castigat

                                    isOver = 1;
                                    for(i = 0; i < 5; i++)
                                        mvaddch(row * 4, x + i * 4, input[i] | COLOR_PAIR(1));
                                    mvprintw(LINES / 2 + 3, COLS / 2 + 21, "Ai castigat!");
                                    refresh();
                                    delaySeconds(3);
                                    erase();
                                    refresh();
                                    return 2;

                                } else if(row == 6) { //am pierdut

                                    isOver = 1;
                                    mvprintw(LINES / 2 + 3, COLS / 2 + 21, "Ai pierdut!");
                                    mvprintw(LINES / 2 + 4, COLS / 2 + 18, "Cuvantul era %s!", word);
                                    refresh();
                                    delaySeconds(5);
                                    erase();
                                    refresh();
                                    return 2;

                                } else { //pun in stanga ce s-a folosit

                                    for(i = 0; i < 5; i++)
                                        if(letterExists(input[i], i, word) == 2) {
                                            mvaddch(row * 4, x + i * 4, input[i] | COLOR_PAIR(1));
                                            letters(input[i] - 32, COLOR_PAIR(1));
                                        }
                                        else if(letterExists(input[i], i, word)) {
                                                mvaddch(row * 4, x + i * 4, input[i] | COLOR_PAIR(2));
                                                letters(input[i] - 32, COLOR_PAIR(2));
                                        }
                                            else {
                                                mvaddch(row * 4, x + i * 4, input[i] | COLOR_PAIR(8));
                                                letters(input[i] - 32, COLOR_PAIR(8));
                                            }
                                    row++; //dau reset la ce trebuie
                                    length = 0;
                                    col = 1;
                                    size = 0;
                                    timeLeft = 30;
                                    for(i = 0; i < 5; i++) {
                                        pos_x -= 2;
                                        mvaddch(pos_y, pos_x, 97 | A_ALTCHARSET);
                                    }
                                }
                            } else if(ch == ':') return controlMenu();

            for(i = 0; i < size; i++)
                mvaddch(row * 4, x + i * 4, input[i]);
            refresh(); //se intampla sa nu sterg bine
        }
    }
    return 2;
}