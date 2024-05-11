    Nume: Nenciu George-Robert
    Grupa: 323CC
    Probleme rezolvate: 5 / 5
    Punctaj local: 150 / 150p
    Timp petrecut rezolvand problemele:
    | -> Servere: ~ 3 ore       25 / 25p
    | -> Colorare: ~ 3 ore      25 / 25p
    | -> Compresie: ~ 1 ora     25 / 25p
    | -> Criptat: ~ 3 ore       30 / 30p
    | -> Oferta: ~ 4 ore        35 / 35p
    |--------------------

! Eu folosesc pe VSC o extensie numita Better Comments care face ca unele co-
mentarii sa fie colorate in functie de ce e pus dupa //:
- * -> verde    (il folosesc pentru etapele de rezolvare)
- ? -> albastru (il folosesc pentru informatii in plus)
- nimic -> gri
- ! -> rosu     (il folosesc daca e ceva important)
- TODO: -> portocaliu

# Servere
    Dupa citire, caut puterea minima si maxima necesara in O(n). Acestea ofera
intervalul in care se afla rezultatul. Cu un fel de cautare binara, caut maxi-
mul local pe un interval de forma [mid - 1; mid + 1] in 5 puncte: mid - 1,
mid - 0.5, mid, mid + 0.5 si mid + 1. Daca valoarea maxima locala se afla la o
limita, mut mijlocul pe partea intreaga a acesteia si merg mai departe. Aceasta
cautare binara se termina in maxim O(log m), unde m este valoarea maxima din
interval si nu depinde de n. De aici reiese ca avem ca si complexitate O(n *
log m), unde m e puterea maxima citita.

# Colorare
    A durat ceva timp pana am realizat ca formulele se schimba in functie de ca-
re este prima pereche citita. Se observa urmatoarele reguli (x si y reprezinta
numere arbitrare):
    x H -> 2 * 3^(x - 1) posibilitati
    y V -> 3 * 2^(y - 1) posibilitati

    H -> H in 3 moduri
    H -> V intr-un mod
    V -> H in 2 moduri
    V -> V in 2 moduri

    Daca prima pereche este cu V, coeficientul ramane 3
    Daca prima pereche este cu H, coeficientul este 6 (cu 2 orizontale le pot
colora in 3 feluri)

    Tinand cont de aceste reguli, voi citi perechile si la fiecare pas calculez
produsul dintre puteri si coeficienti in functie de reguli. Pentru parcurgere e
nevoie de O(n) iar pentru ridicare la putere (pe care o fac logaritmic) este
nevoie de O(log x) unde x elementul din care se va calcula cel mai greu puterea.
De aici rezulta ca avem ca si complexitate O(n * log x).

# Compresie
    Daca sumele vectorilor nu sunt egale, atunci inseamna ca oricum le-am scrie,
nu putea aduna elemente pentru a forma o compresie, deci rezultatul e -1. Daca
se poate, iau doua variabile care memoreaza la ce element ma aflu in fiecare
vector si fac sume partiale. Daca suma dintr-un vector este mai mare decat cea-
lalta, adun doar elemente din acela pana suma fie e egala, fie depaseste. Daca
sumele sunt egale, am gasit un element, deci as putea adauga un element in noul
vector. Repet chestia asta pana ramane cel mult un vector cu elemente si la fi-
nal verific daca cu ultimele elemente sumele sunt egale.
    Cum doar parcurg de doua ori elementele fara sa ma intorc, complexitate es-
te O(2 * n), deci O(n).

# Criptat
    Problema seamana foarte mult cu problema rucsac, doar ca nu se aplica pe
toate caracterele direct. Mai intai citesc cuvintele, memorez caracterele cu
o complexitate pentru citire de O(n), urmand sa am un vector cu (cel mult) 8
caractere distincte si o matrice care cunoaste pentru fiecare caracter numa-
rul de aparitii pentru fiecare cuvant. Ca la rucsac voi considera greutate
ca fiind lungimea cuvantului si profitul ca fiind numarul de aparitii. Daca
profitul maxim local este mai mare decat jumatate decat indexul la care se
afla, atunci parola ce se poate obtine are caracter dominant. Compar cu ceilal-
ti maximi locali si obtin rezultatul final.
    Cum rucsac se rezolva in O(n * W), unde W este greutate pe care o poate a-
avea rucsacul, aici W va fi L (sau in implementare total) care reprezinta lun-
gimea maxima posibila ce se poate realiza cu toate cuvintele. Dar cum noi apli-
cam solutia "rucsac" pentru maxim 8 caractere => O(8 * n * L) = O(n * L).

# Oferta
    Dupa citirea preturilor fiecarui produs, folosind programare dinamica, pre-
calculez ultimele k (daca se poate, daca sunt mai putine, calculez cate sunt)
la fiecare pas.
    Daca n e 1 => rezultatul e chiar pretul produsului
    Daca n e 2 => rezultatul e pretul gruparii celor doua produse
    Daca n >= 3 => rezultatul e cominatie intre suma dintre pereche sau trio de
produse. Pentru a afla, la fiecare pas i memorez sumele anterioare si caut mereu
minimul. Cand ajung la ultimul produs, am cel putin ultimele k sume. Daca n e
prea mic, atunci k > numarul de sume existente, deci rezultatul este -1.
    flag este utilizat pentru a verifica daca am pus cele mai mici k sume in-
tr-un vector precedent.
    Solutia este in dp[n][k - 1] mereu daca am cel putin k sume.
    Pentru a calcula la fiecare pas cele mai mici k sume, am nevoie sa adaug
3 * k elemente in vectorul actual, cel precedent si cel anteprecedent, deci o
complexitate de O(k) si chestia asta se intampla de n ori (2 <= i < n cu pa-
sul 1), deci complexitate solutiei este O(n * k).