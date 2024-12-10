# Task lcg-otp
    Mai intai fac rost de mesajul criptat. Il adaug manual in ``decrypt.cpp``.
Voi apela o comanda pentru a decripta din base64 si rezultatul va fi binar.
    Solutia este simpla: brute force. Cum flagul contine in mesaj ``Speis...``,
inseamna ca pot face un brute force attack in care verific daca mesajul contine
subsirul. Iau toate valorile (inclusiv) intre 1337 si 10.000 pentru a si b si
aplic xor intre mesajul criptat si cheia generata deoarece obtin mesajul ini-
tial. La final este afisat mesajul cautat si parametrii.
    Am folosit o singura functie care e pe stack overflow pentru a citi un fi-
sier fara a avea habar care e size-ul sau.

ref: https://stackoverflow.com/questions/15366319/how-to-read-the-binary-file-in-c

# Task unexpected-ceo

    M-am uitat la cheia publica si am observat ca ma pot conecta prin ssh la
hacker@isc2024.1337.cx. Ca si la un exercitiu de la lab, am folosit comanda
    ```cat /etc/shadow```
    Am observat ca am un user numit ``secretary_m1str3s`` si un hash care
ar trebui sa fie usor de spart (am aflat din mai multe incercari ca are 4 ca-
ractere parola). Am folosit ``John the Ripper`` ca sa ii aflu parola, am vazut
ce contine home-ul ceo-ului si m-am uitat in fisierul ``generate_report.sh``.
    Avand comanda ``sh -c`` in ea, si putand apela comenzi cu ``sudo`` in lo-
cul acestuia, cand astepta input am folosit urmatoarele comenzi pe rand:
    ```; ls -la /home/l33t_ceo;```
    ```; ls -la /home/l33t_ceo\.invalid-directory;```
    Am gasit un fisier numit ``zflag.x``, pe care l-am deschis, obtinand flagul
cautat.

# Task binary-database

    Observam ca programul nu are protectie pe stiva, deci putem face buffer o-
verflow. In ```process_loop``` gasim un vector aflat la 0x5b fata de stiva. Cum
exista 4 biti pentru return, asta inseamna ca pentru payload functiei sunt 91
(0x5b) - 4 = 87.
    In ghidra se observa ca exista o functie care neapelata: ``db_first_flag``.
In acesta avem un argument de tip unsigned int care e comparata cu o variabila
globala (valoarea ei este 31337F64). Aici se regaseste flagul.
    Pentru a ajunge aici, lua flagul si de a iesi din functie (mai e o varia-
bila len care da eroare daca inputul are lungime mai mare de 85), trebuie sa
facem urmatoarele:
    1. e nevoie de un payload de contine 87 * ch (ajungem pe ebp) + 4 * ch
(schimbam adresa de return) + 080497F8 (adresa lui ``db_first_flag``) + 4 *
ch + 31337F64 (valoare variabilei globale), unde ch e un caracter arbitrar
    Adica 87 * ch + 4 * ch + 080497F8 + 4 * ch + 31337F64.

    2. se trimite mai intai lungimea payloadului ca sa suprascrie ca e citit
prima oara pe server (adica 103)

    3. se trimite payloadul

    4. se trimite 0 in 4 biti pentru a iesi din functie si pentru a primi
flagul