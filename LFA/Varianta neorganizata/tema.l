/** Nenciu George-Robert 333CC **/

%{  /** declarations **/
    #include <bits/stdc++.h>
    #include <cstring>

    enum Grammar_type {
        GFR = 0,
        GDC = 1,
        GIC = 2,
        GR = 3
    };

    typedef struct {
        std::string src;
        std::vector<std::pair<std::string, std::string>> ways;
    } Way;

    enum Grammar_type g = GR;

    std::vector<std::string> file_paths;
    std::string name;

    //* variable
    std::string var_name;
    std::vector<std::string> var_values;

    //* alphabet
    std::vector<std::string> alphabet;

    //* number of products
    int prod_num = 0;

    //* grammar types
    bool can_gr, can_gic, can_gdc, has_noterm, is_lower, is_upper, aux;

    //* automatata states
    std::vector<std::string> states, final_states;
    std::vector<Way> follow_pos;
    std::string start, letter, next_state;
    Way w;

    //* check deterministic type
    bool is_deterministic;
%}

%option noyywrap

%x Variable Vars Variable_loc_g Vars_loc_g Variable_loc_a Vars_loc_a
%x Nonterm Start Grammar Product Left_product And Alphabet_g
%x States Final Automata Initial Letter Follow Alphabet_a

WORD [a-zA-Z0-9_]
UWORD [A-Z]{WORD}*
LWORD [a-z]{WORD}*
TAB [ \t]
COL {TAB}::{TAB}
EQ {TAB}::={TAB}

%%  /** rules **/
%\s+ {}  /* I don't need spaces at start*/
%\t+ {}  /* I don't need tabs at start*/
^%.*\n {}  /* single line comment to ignore */
\/\*([^*]|\*+[^*/])*\*+\/ {}  /* multi line comment to ignore */
<*>[ ]*%.*\n {}  /* single line comment to ignore */
<*>\/\*([^*]|\*+[^*/])*\*+\/ {}  /* multi line comment to ignore */

\s*{WORD}+\.txt { file_paths.push_back(yytext); } /* files to read from */

variable{TAB} { BEGIN(Variable); }  /* global variable */
<Variable>{WORD}* { var_name = yytext; }
<Variable>{EQ} {}  /* used for debugging */
<Variable>\{ { var_values.clear(); BEGIN(Vars); }  /* read until bracket */
<Vars>{LWORD} { var_values.push_back(yytext); }
<Vars>. {}  /* I don't care about other characters */
<Vars>\n {
    std::cout << "\nVariabila globala:"
              << "\n\tIdentificator: " << var_name
              << "\n\tDomeniu: {";

    for (size_t i = 0; i < var_values.size() - 1; i++)
        std::cout << var_values[i] << ", ";

    std::cout << var_values[var_values.size() - 1] << "}\n";

    BEGIN(INITIAL);
    }  /* values are read, go back to grammar / automata */

Grammar {
    std::cout << "\nNumele gramaticii: " << name << "\n";
    g = GR;
    can_gr = can_gic = can_gdc = true;
    has_noterm = false; aux = false;
    BEGIN(Grammar);
    }
FiniteAutomaton {
    std::cout << "\nNumele automatului: " << name << "\n";
    is_deterministic = true;
    BEGIN(Automata);
    }
{WORD}* {
    prod_num = 0;
    name = yytext;
    start = "-1";
    var_name = "-1";
    states.clear();
    w.ways.clear();
    alphabet.clear();
    follow_pos.clear();
    var_values.clear();
    final_states.clear();
    }  /* get then name of the grammar / automata */
.|\n {}

<Grammar>{TAB}variable{TAB} { BEGIN(Variable_loc_g); }  /* local variable in grammar */
<Variable_loc_g>{WORD}* { var_name = yytext; }
<Variable_loc_g>{EQ} {}  /* used for debugging */
<Variable_loc_g>\{ { BEGIN(Vars_loc_g); }  /* read until bracket */
<Vars_loc_g>{LWORD} { var_values.push_back(yytext); }
<Vars_loc_g>. {}  /* I don't care about other characters */
<Vars_loc_g>\n { BEGIN(Grammar); }  /* values are read, go back to grammar */

<Grammar>{TAB}nonterminals{COL} { BEGIN(Nonterm); } /* nonterminals in grammar */
<Nonterm>{UWORD} {}  /* "loop" through the words only */
<Nonterm>. {}   /* I don't care about other characters */
<Nonterm>\n {BEGIN(Grammar);}  /* nonterminals are read, go back to grammar */

<Grammar>{TAB}alphabet{TAB} { BEGIN(Alphabet_g); }
<Alphabet_g>{LWORD} { alphabet.push_back(yytext); }  /* "loop" through the words only */
<Alphabet_g>. {}  /* I don't care about other characters */
<Alphabet_g>\n { BEGIN(Grammar); }  /* alphabet is read, go back to grammar */

<Grammar>{TAB}start_symbol{COL} { BEGIN(Start); }
<Start>{UWORD} {}
<Start>. {}  /* I don't care about other characters */
<Start>\n { BEGIN(Grammar); }  /* symbol is read, go back to grammar */

<Grammar>{TAB}{LWORD} { can_gic = false; BEGIN(Left_product); }
<Grammar>{TAB}{UWORD} { aux = true; BEGIN(Left_product); }
<Left_product>{UWORD} { can_gr = false; if (aux) is_upper = true; }
<Left_product>{LWORD} { can_gr = false; is_upper = false; }
<Left_product>\& {}  /* used for debugging */
<Left_product>. {}  /* I don't care about other characters */
<Left_product>\-\> {aux = false; BEGIN(Product); }  /* left read, go to right of the rule */
<Product>{UWORD} { has_noterm = true; BEGIN(And); }  /* get the product while finding UWORD & WORD */
<Product>{LWORD} { is_lower = true; BEGIN(And); }  /* get the product while finding LWORD & WORD */
<Product>. { prod_num++; BEGIN(And); }  /* I don't care about other characters */
<And>{UWORD} {
    if (has_noterm) can_gr = false;
    else has_noterm = true;
    is_lower = false;
    }
<And>{LWORD} { if (has_noterm) can_gr = false; else is_lower = true; }
<And>\& {}  /* used for debugging */
<And>\| {
    if (!has_noterm) is_lower = true;
    has_noterm = false;
    prod_num++;
    }  /* check if grammar is less restricted */
<And>\; {
    if (can_gdc && is_upper && is_lower) can_gdc = false;
    has_noterm = is_upper = is_lower = aux = false;
    BEGIN(Grammar);
    }  /* rule is read, go back to grammar */
<And>. {}  /* I don't care about other characters */
<Product>\n { BEGIN(Grammar); }  /* line completely read, go further */

<Grammar>.|\n {} /* I don't care about newline */
<Grammar>;; { /* output everything about grammar */
    std::string output;

    /* get the most restricted grammar type */
    if (!can_gr) g = GIC;
    if (!can_gic) g = GDC;
    if (!can_gdc) g = GFR;

    /* remember the type as string */
    switch (g) {
        case GFR: output = "GFR"; break;
        case GDC: output = "GDC"; break;
        case GIC: output = "GIC"; break;
        case  GR: output =  "GR"; break;
        default:
            std::cerr << "Grammar error. Aborted.\n";
            exit(1);
    }

    std::cout << "Tipul gramaticii: " << output
              << "\nNumarul de reguli de productie: " << prod_num
              << "\nAlfabetul gramaticii: {";

    for (size_t i = 0; i < alphabet.size() - 1; i++)
        std::cout << alphabet[i] << ", ";

    std::cout << alphabet[alphabet.size() - 1] << "}\n";

    /* there is a local variable */
    if (var_name != "-1") {
        std::cout << "Variabila locala:"
                  << "\n\tIdentificator: " << var_name
                  << "\n\tDomeniu: {";

        for (size_t i = 0; i < var_values.size() - 1; i++)
            std::cout << var_values[i] << ", ";

        std::cout << var_values[var_values.size() - 1] << "}\n";
    }

    /* get next input */
    BEGIN(INITIAL);
    }  /* grammar is fully read */

<Automata>{TAB}variable{TAB} { BEGIN(Variable_loc_a); }
<Variable_loc_a>{WORD}* { var_name = yytext; }
<Variable_loc_a>{EQ} {}
<Variable_loc_a>\{ { BEGIN(Vars_loc_a); }  /* read until bracket */
<Vars_loc_a>{LWORD} { var_values.push_back(yytext); }
<Vars_loc_a>. {} /* I don't care about other characters */
<Vars_loc_a>\n { BEGIN(Automata); }  /* values are read, go back to automata */

<Automata>{TAB}alphabet{TAB} { BEGIN(Alphabet_a); }
<Alphabet_a>{LWORD} { alphabet.push_back(yytext); }
<Alphabet_a>. {} /* I don't care about other characters */
<Alphabet_a>\n { BEGIN(Automata); } /* alphabet is read, go back to automata */

<Automata>{TAB}states{TAB} { BEGIN(States); }
<States>{LWORD} { states.push_back(yytext); }
<States>. {} /* I don't care about other characters */
<States>\n { BEGIN(Automata); } /* states are read, go back to automata */

<Automata>{TAB}final_states{TAB} { BEGIN(Final); }
<Final>{LWORD} { final_states.push_back(yytext); }  /* "loop" through final states */
<Final>. {} /* I don't care about other characters */
<Final>\n { BEGIN(Automata); } /* final states are read, go back to automata */

<Automata>{TAB}initial_state{TAB} { BEGIN(Initial); }
<Initial>{LWORD} { start = yytext; }
<Initial>. {} /* I don't care about other characters */
<Initial>\n { BEGIN(Automata); } /* initial states is read, go back to automata */

<Automata>({LWORD}|{UWORD}) {  /* remember previous state */
    w.src = yytext;
    BEGIN(Letter);
    }
<Letter>{LWORD} { letter = yytext; BEGIN(Follow); }  /* remember condition */
<Follow>({LWORD}|{UWORD}) {  /* remember q_prev -> (using letter) -> q_next */
    next_state = yytext;

    if (letter == var_name) {  /* this is a local variable */
        for (std::string str : var_values)
            w.ways.push_back({str, next_state});
    } else w.ways.push_back({letter, next_state}); /* not variable */

    if (letter == "e" || w.ways.size() > alphabet.size()) is_deterministic = false;

    BEGIN(Letter);
    }
<Follow>. {} /* I don't care about other characters */
<Letter>\) { follow_pos.push_back(w); w.ways.clear(); BEGIN(Automata); } /* get next state */
<Letter>.|\n {} /* I don't care about other characters */

<Automata>.|\n {} /* I don't care about other characters */
<Automata>;; { /* output everything about automata */
    std::cout << "Tipul automatului: Automat finit "
              << (is_deterministic ? "" : "ne") << "determinist"
              << "\nAlfabetul de intrare: {";

    for (size_t i = 0; i < alphabet.size() - 1; i++)
        std::cout << alphabet[i] << ", ";

    std::cout << alphabet[alphabet.size() - 1] << "}";

    std::cout << "\nNumarul de stari: " << states.size()
              << "\nStarea initiala: " << start
              << "\nStarile finale: {";

    for (size_t i = 0; i < final_states.size() - 1; i++)
        std::cout << final_states[i] << ", ";

    std::cout << final_states[final_states.size() - 1] << "}\n";

    std::cout << "Functia de tranzitie:\n";

    for (auto a : follow_pos) {
        std::string src = a.src;

        for (auto b : a.ways)
            std::cout << "\tm(" << src << ", " << b.first << ") = "
                      << b.second << "\n";
    }

    /* there is a local variable */
    if (var_name != "-1") {
        std::cout << "Variabila locala:"
                  << "\n\tIdentificator: " << var_name
                  << "\n\tDomeniu: {";

        for (size_t i = 0; i < var_values.size() - 1; i++)
            std::cout << var_values[i] << ", ";

        std::cout << var_values[var_values.size() - 1] << "}\n";
    }

    BEGIN(INITIAL);
    }  /* automata is fully read */
%%

void check(bool cond, std::string msg, std::string func_name) {
    if (!cond) return;  //* the bad thing doesn't happen

    std::cerr << "In function " + func_name + " gave the error: " + msg + ".\n";

    exit(-1);  //* closes everything
}


void yyerror(const char* err_msg) {
    fprintf(stderr, "Error found: %s\n", err_msg);
}


int main(int argc, char** argv) {
    check(argc < 2, "more arguments needed", "main");

    //* read the input files
    for (size_t file_id = 1; file_id < argc; file_id++) {
        FILE *fin = fopen(argv[file_id], "r");

        check(!fin, "invalid path", "main");

        yyin = fin;
        yylex();  //* read from file
        fclose(fin);
    }

    return 0;
}