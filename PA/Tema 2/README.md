    Nume: Nenciu George-Robert
    Grupa: 323CC
    Probleme rezolvate: 4 / 4
    Punctaj local: 150 / 150p
    Timp petrecut rezolvand problemele:
    | -> Numarare: ~ 1 ore      35 / 35p
    | -> Trenuri: ~ 2 ore       40 / 40p
    | -> Drumuri: ~ 4 ora       40 / 40p
    | -> Scandal: ~ 4 ore       25 / 25p
    |-----------------------------------

! Eu folosesc pe VSC o extensie numita Better Comments care face ca unele co-
mentarii sa fie colorate in functie de ce e pus dupa //:
- * -> verde    (il folosesc pentru etapele de rezolvare)
- ? -> albastru (il folosesc pentru informatii in plus)
- nimic -> gri
- ! -> rosu     (il folosesc daca e ceva important)
- TODO: -> portocaliu

! Pentru a implementa algoritmii Dijkstra si de sortare topologica m-am insipi-
rat (am folosit ideea de baza de la fiecare) de pe site-ul https://www.geeksforgeeks.org.

# Numarare
    Pentru a citi graful, creez doua grafuri: primul este chiar cel care este
citit, iar al doilea este se construieste in functie de primul daca exista mu-
chie comuna. Aceasta chestie duce in O(n * m), deoarece caut pentru fiecare mu-
chie (in cel mai rau caz) printre n - 1 noduri.
    Problema se rezolva dinamic. Considerand vectorul dp, dp[1] reprezinta lan-
tul dintre primul nod si el insusi (deci e unica). Daca adaug 2 noduri, se pot
forma maxim 2 lanturi prin adunare celor anterioare, deci regula generala este
d[nod_vecin] = d[nod_vecin] + d[nod], la care adaugam % MOD pentru ca se cere.
Cum graful este unul orientat aciclic, inseamna ca pot avea pentru un nod max-
im m - 1 vecini. Algoritmul ar fi fost in O(n * n) daca nu exista restrictia,
deci implementare este in O(n * m).

# Trenuri
    Din ce imi aduc aminte, std::unordered_map are pentru fiecare operatie, de
obicei, complexitate O(1) daca nu exista coliziuni, iar in cel mai rau caz O(n).
Deci o sa consider ambele si notez cu O(UMAP) pentru usurinta.
    Pentru a lucra usor si pentru nu a consuma foarte multa memorie, am folosit
std::unordered_map ca un dictionar. Prima linie contine sursa si destinatia, a-
sa ca am pus ca indici pentru ei 1 si 2 (ex: "Bucuresti" -> "Timisoara" este
tinut minte in dict pe pozitia 1, resp 2).
    Urmeaza a fi citite toate rutele. Mai intai verific daca deja am orasele in
dictionar in O(UMAP) de m ori, deci O(m * UMAP).
    Folosind o stiva fac o sortare topologica pentru a vede in ce moment ajung
in fiecare nod. Astfel, destinatia va contine numarul de muchii prin care am
trecut. TopoSort are ca si complexitate O(n + m).
    In concluzie, algoritmul are ca si complexitate O(n + m * UMAP).

# Drumuri
    In citire construiesc graful cat si opusul grafului (daca in graf avem mu-
chia x -> y, in opusa ei avem x <- y). Deci O(n).
    Vom apela de 3 ori Dijkstra, de doua ori in graful g din nodurile x si y,
iar a 3-a oara in r din nodul z. Caut drumurile din z spre x si y care sa fie
cele mai scurte si apoi verific daca nu se intersecteaza, deoarece poate exis-
ta unul mai scurt. Complexitate pentru Dijkstra este O(m * lg n), iar pentru
a verifica cel mai scurt drum din x si y spre z, este O(n).
    In concluzie, algoritmul este in O(n + m * lg n).

# Scandal
    Consider graful ca avand 2 * n noduri (indexati de la 1 la 2 * n + 1). No-
dul x iar "opusul" lui (cea care e folosita in legarea regulilor), este consi-
derata ca fiind x + n (cea care implica ca daca nu vine, nici celalalt nu vi-
ne). Citirea se face in O(n).
    Sortarea topologica este modificata. Mai intai se pregateste din citire
o ordine, dupa care se completeaza. Pentru fiecare nod nevizitat se adauga
la cele ramase. Urmeaza dfs-ul putin modificat astfel incat sa adauge nivelul
pe care se afla fiecare nod (gradul de prioritate dupa care se stabileste cine
vine si cine nu). Complexitatea ramane O(n + m) deoarece avem vectorul isVisi-
ted care verifica daca am trecut prin noduri sau nu.
    Penultimul for verifica daca "opusul" are prioritate mai mare decat el, da-
ca nu, atunci acesta poate veni si este adaugat in rezultatul final.
    Ca si ultimul for, ambele sunt in O(n), deci algoritmul are ca complexitate
O(n + m).
