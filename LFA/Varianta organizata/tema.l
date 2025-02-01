/** Nenciu George-Robert 333CC **/
%option noyywrap

%x VARIABILIA LOOP

%x NON SIMBOL
%x LOCALA_GRAM LOOP_GRAM ALFA_GRAM
%x GRAMATICA REGULA REGULA_START REGULA_NEXT

%x LOCALA_AUTO LOOP_AUTO
%x AUTOMAT STARE_IN STARE FOL_POS ALFA_AUTO
%x STARI STARI_FIN

%{
    #include <bits/stdc++.h>

    using namespace std;

    typedef pair<string, string> dir;

    typedef struct Variable {
        string name;
        vector<string> values;

        Variable() {}

        Variable(string name, vector<string> values) {
            this->name = name;
            this->values = values;
        }

        void add(string val) { values.push_back(val); }
        void clear() { name = "-1"; values.clear(); }

        void display(string type) {
            cout << "Variabila " + type + ":\n";
            cout << "\tIdentificator: " + name + "\n";
            cout << "\tDomeniu: {";

            for (auto it = values.begin(); it != values.end(); it++) {
                if (next(it) == values.end()) {
                    cout << *it << "}\n\n";
                    break;
                }

                cout << *it << ", ";
            }
        }
        void dcls(string type) { display(type); clear(); }
    } Variable;

    typedef struct Letters {
        vector<string> names;

        void add(string name) { names.push_back(name); }

        void display(string prop) {
            cout << prop + ": {";

            for (auto it = names.begin(); it != names.end(); it++) {
                if (next(it) == names.end()) {
                    cout << *it << "}\n\n";
                    break;
                }

                cout << *it << ", ";
            }
        }

        void clear() { names.clear(); }
        void dcls() { this->display(""); this->clear(); }
    } Letters;

    typedef struct Product {
        vector<string> products;

        void add(string product) { products.push_back(product); }
        void clear() { products.clear(); }
    } Product;

    typedef struct Follow {
        vector<dir> d;
        string start;
    } Follow;

    typedef struct Grammar {
        Variable global, local;
        Letters nonterminal, alphabet;
        string start, name;
        Product start_product, end_product;
        int type;  // tipul gramaticii
        int r; // numarul de reguli
        bool upp, low; // incepe cu litera mica sau mare
        bool up; // tine minte daca regula a avut litera mare pentru restrictii
        bool non; // are nonterminali

        void reset() { upp = up = non = false; low = true; }

        void clear() {
            global.clear();
            local.clear();
            nonterminal.clear();
            alphabet.clear();
            start_product.clear();
            end_product.clear();
            type = 4;
            r = 0;
            reset();
        }

        void display() {
            cout << "Numele gramaticii: " << name << "\n";

            string rule;

            if (type == 1) rule = "GFR";
            if (type == 2) rule = "GDC";
            if (type == 3) rule = "GIC";
            if (type == 4) rule = "GR";

            cout << "Tipul gramaticii: " + rule + "\n";
            cout << "Numarul de reguli de productie: " << r << "\n";

            alphabet.display("Alfabetul gramaticii");

            if (local.name != "-1") local.display("locala");
        }

        void lower_type(int type) { // daca gramatica are mai putine restrictii
            if (type < this->type) this->type = type; // nu am ce modifica
        }
    } Grammar;

    typedef struct Automata {
        Variable global, local;
        Letters nonterminal, alphabet, sts, fts; // stari (+ finale)
        vector<Follow> q;
        bool det; // verifica daca e determinist
        string start; // prima stare
        string name; // numele automatului
        string src; // verific daca am variabila la trecerea in stari
        Follow tmp;

        void clear() {
            global.clear();
            local.clear();
            nonterminal.clear();
            alphabet.clear();
            sts.clear();
            fts.clear();
            q.clear();
            det = true;
            tmp.d.clear();
        }

        void display() {
            string out;
            if (det) {
                out = "determinist";
            } else {
                out = "nedeterminist";
            }

            cout << "Numele automatului: " + name + "\n";
            cout << "Tipul automatului: Automat finit " + out << "\n";

            alphabet.display("Alfabetul de intrare");

            cout << "Numarul de stari: " << sts.names.size() << "\n";
            cout << "Starea initiala: " + start + "\n";

            fts.display("Starile finale");

            cout << "Functia de tranzitie:\n";

            for (auto it = q.begin(); it != q.end(); it++) {
                tmp = *it;

                for (auto itd = tmp.d.begin(); itd != tmp.d.end(); itd++) {
                    cout << "\t" << "m(" << tmp.start;
                    cout << ", " << itd->first + ") = ";
                    cout << itd->second + "\n";
                }
            }

            if (local.name != "-1") local.display("locala");
        }
    } Automata;

    Variable global;
    Grammar gr;
    Automata au;
%}

%%
<*>[ ]*%.*\n {}  /* ignor comentariul de un rand la orice regula */
<*>\/\*([^*]|\*+[^*/])*\*+\/ {}  /* ignor comentariul de mai multe randuri la orice regula */

variable[ \t] { BEGIN(VARIABILIA); } /* am variabila globala */
[ \t]*Grammar { gr.reset(); gr.global = global; BEGIN(GRAMATICA); }
[ \t]*FiniteAutomaton { BEGIN(AUTOMAT); }
[a-zA-Z0-9_]* { gr.clear(); au.clear(); gr.name = yytext; au.name = yytext; } /* numele */
. {}
\n {} //

<VARIABILIA>[a-zA-Z0-9_]* { global.name = yytext; } /* variabila globala daca exista */
<VARIABILIA>\{ { BEGIN(LOOP); }  /* citesc fiecare litera */
<VARIABILIA>. {}
<LOOP>[a-z][a-zA-Z0-9_]* { global.add(yytext); }
<LOOP>. {}
<LOOP>\n { global.dcls("globala"); BEGIN(INITIAL); } /* am citit */

<GRAMATICA>[ \t]variable[ \t] { BEGIN(LOCALA_GRAM); } /* variabila locala */
<GRAMATICA>[ \t]nonterminals { BEGIN(NON); } /* nonterminali */
<GRAMATICA>[ \t]alphabet { BEGIN(ALFA_GRAM); } /* alfabet */
<GRAMATICA>[ \t]start_symbol { BEGIN(SIMBOL); } /* simbol de inceput */
<GRAMATICA>[ \t][a-z][a-zA-Z0-9_]* { gr.lower_type(2); BEGIN(REGULA_START); } /* incepe cu litera mica */
<GRAMATICA>[ \t][A-Z][a-zA-Z0-9_]* { gr.up = true; BEGIN(REGULA_START); } /* incepe cu litera mare */
<GRAMATICA>\n {}
<GRAMATICA>. {}
<GRAMATICA>;; { gr.display(); BEGIN(INITIAL); }  /* sfarsitul fisierului */

<LOCALA_GRAM>[a-zA-Z0-9_]* { gr.global.name = yytext; } /* numele gramaticii */
<LOCALA_GRAM>\{[ \t] { BEGIN(LOOP_GRAM); } /* urmeaza sa citesc fiecare litera */
<LOCALA_GRAM>. {}
<LOOP_GRAM>[a-z][a-zA-Z0-9_]* { gr.global.add(yytext); }
<LOOP_GRAM>. {}
<LOOP_GRAM>\n { BEGIN(GRAMATICA); } /* am citit */

<NON>[A-Z][a-zA-Z0-9_]* { gr.nonterminal.add(yytext); } /* citesc fiecare cuvant */
<NON>. {}
<NON>\n {BEGIN(GRAMATICA);} /* am citit */

<ALFA_GRAM>[a-z][a-zA-Z0-9_]* { gr.alphabet.add(yytext); } /* citesc fiecare cuvant */
<ALFA_GRAM>. {}
<ALFA_GRAM>\n { BEGIN(GRAMATICA); } /* am citit */

<SIMBOL>[A-Z][a-zA-Z0-9_]* { gr.start = yytext; } /* citesc simbolul de inceput */
<SIMBOL>. {}
<SIMBOL>\n { BEGIN(GRAMATICA); } /* am citit */

<REGULA_START>[A-Z][a-zA-Z0-9_]* {
    gr.lower_type(3); // nu poate fi gramatica regulata
    if (gr.up)
        gr.upp = true;
    gr.start_product.add(yytext);
}
<REGULA_START>[a-z][a-zA-Z0-9_]* { gr.lower_type(3); gr.upp = false; gr.start_product.add(yytext); }
<REGULA_START>. {}
<REGULA_START>\-\> { gr.up = false; BEGIN(REGULA); }  /* in ce stari pot ajunge */
<REGULA>[A-Z][a-zA-Z0-9_]* { gr.non = true; gr.end_product.add(yytext); BEGIN(REGULA_NEXT); }  /* am nonterminal */
<REGULA>[a-z][a-zA-Z0-9_]* { gr.end_product.add(yytext); BEGIN(REGULA_NEXT); }  /* am litera */
<REGULA>. { gr.r++; BEGIN(REGULA_NEXT); }  /* citesc regula */
<REGULA_NEXT>[A-Z][a-zA-Z0-9_]* {
    gr.end_product.add(yytext);
    if (gr.non)
        gr.lower_type(3); // nu poate fi gramatica regulata
    else
        gr.non = true;
    gr.low = false;
}
<REGULA_NEXT>[a-z][a-zA-Z0-9_]* {
    gr.end_product.add(yytext);
    if (gr.non)
        gr.lower_type(3);
}
<REGULA_NEXT>\| { gr.end_product.add(yytext); gr.non = false; gr.r++; }  /* verific daca am nonterminali in regula */
<REGULA_NEXT>\; {
    if (gr.upp && gr.low)
        gr.lower_type(1); // e sigur gfr
    gr.reset();
    BEGIN(GRAMATICA);
    }  /* productia e citita */
<REGULA_NEXT>. {}
<REGULA>\n { BEGIN(GRAMATICA); }  /* randul e citit */

<AUTOMAT>[ \t]*variable[ \t]* { BEGIN(LOCALA_AUTO); }
<AUTOMAT>[ \t]*alphabet[ \t]* { BEGIN(ALFA_AUTO); } /* urmeaza literele */
<AUTOMAT>[ \t]*states[ \t]* { BEGIN(STARI); } /* urmeaza starile */
<AUTOMAT>[ \t]*final_states[ \t]* { BEGIN(STARI_FIN); }
<AUTOMAT>[ \t]*initial_state[ \t]* { BEGIN(STARE_IN); } /* urmeaza starea initiala */
<AUTOMAT>([a-z][a-zA-Z0-9_]*|[A-Z][a-zA-Z0-9_]*) { au.tmp.start = yytext; BEGIN(STARE); } /* iau stare din care se pleaca */
<AUTOMAT>. {}
<AUTOMAT>\n {}
<AUTOMAT>;; { au.display(); BEGIN(INITIAL); } /* am citit fisierul despre automat si acum afisez */

<LOCALA_AUTO>[a-zA-Z0-9_]* { au.local.name = yytext; }
<LOCALA_AUTO>[ \t]*::=[ \t]* {}
<LOCALA_AUTO>\{ { BEGIN(LOOP_AUTO); } /* urmeaza literele */
<LOOP_AUTO>[a-z][a-zA-Z0-9_]* { au.local.add(yytext); }
<LOOP_AUTO>. {}
<LOOP_AUTO>\n { BEGIN(AUTOMAT); } /* am trecut de } */

<ALFA_AUTO>[a-z][a-zA-Z0-9_]* { au.alphabet.add(yytext); }
<ALFA_AUTO>. {}
<ALFA_AUTO>\n { BEGIN(AUTOMAT); } /* am gasit cap de rand */

<STARI>[a-z][a-zA-Z0-9_]* { au.sts.add(yytext); }
<STARI>. {}
<STARI>\n { BEGIN(AUTOMAT); } /* am trecut de } */

<STARI_FIN>[a-z][a-zA-Z0-9_]* { au.fts.add(yytext); }  /* urmeaza starile finale */
<STARI_FIN>. {}
<STARI_FIN>\n { BEGIN(AUTOMAT); } /* cap de rand, deci mai departe la starea initiala */

<STARE_IN>[a-z][a-zA-Z0-9_]* { au.start = yytext; }
<STARE_IN>. {}
<STARE_IN>\n { BEGIN(AUTOMAT); } /* am trecut de ; */

<STARE>[a-z][a-zA-Z0-9_]* { au.src = yytext; BEGIN(FOL_POS); }  /* cu ce se trece (poate fi variabila) */
<FOL_POS>([a-z][a-zA-Z0-9_]*|[A-Z][a-zA-Z0-9_]*) {  /* in cine ma duc */
    if (au.src == "e") au.det = false; // nu poate fi determinist cu 'e'
    if (au.src == au.local.name) { // inlocuiesc
        for (auto it = au.local.values.begin(); it != au.local.values.end(); it++) {
            au.tmp.d.push_back({*it, yytext});
        }
    } else au.tmp.d.push_back({au.src, yytext}); // e doar notatia pt destinatie

    if (au.alphabet.names.size() < au.tmp.d.size()) au.det = false; // mai multe legaturi decat litere

    au.q.push_back(au.tmp);
    au.tmp.d.clear();

    BEGIN(STARE);
    }
<FOL_POS>. {}
<STARE>\) { BEGIN(AUTOMAT); } /* get next state */
<STARE>. {} /* astept sa gasesc ) */
<STARE>\n {} /* astept sa gasesc ) */
%%

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Please use ./tema <file1> <file2> <...>.");
        return 1;
    }

    //* read the input files
    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");

        if (!f) {
            perror("File can't be opened.\n");
            exit(1);
        }

        yyin = f;
        yylex();
        fclose(f);
    }

    return 0;
}