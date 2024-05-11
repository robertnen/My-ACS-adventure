    Nume: Nenciu George-Robert
    Materie: PCOM
    Tema: 2
    Nume Tema: Aplicatie client-server TCP si UDP pentru gestionare mesajelor
    Functionalitati implementate:
        - serverul se deschide
        - clientii se pot conecta
        - clientii pot da subscribe / unsubscribe la orice topic
        - fiecare topic este salva pe server intr-o variabila numita moodle :D
        - acestea pot fi transmise catre client
        - etc

    Ore petrecute: aproximativ 20 de ore
    Probleme legate de tema:
        - foarte des bind-ul UDP era blocat pentru fiecare verificare
        - aparent pe checker nu primesc testul data_subscribed
        - aparent pe checker nu primesc testul server_exit (dar merge 100%)
        - nu am reusit sa fac wildcardurile
        - unele variabile nu pot fi puse local/global deoarece apare in checker
    eroare "Broken Pipe" fara motiv

    M-am folosit de laboratorul 7 si de cateve resurse online ale caror link-uri
nu mai merg deoarece au fost sterse / sunt private.

# Parti comune de implementare
    Pentru ambele, am creat functii care trimit erori de comenzi sau erori de
la functii care ar fi trebuie sa mearga corect si sa nu returneze o valoare ne-
gativa.
    Pentru inceput, memorez in program socketurile UDP si TCP folosite in pro-
gram. Folosind functii precum bind si listen, server este pregatit. Folosind
p_fds, in ambele avem pe primul element STDIN, pe al doilea UDP (doar pentru
server) si ultimul TCP. Fiecare asteapta o comanda din terminal.
    Ambele fisiere contin multe randuri de cod dedicate programarii defensive.
Nu exista erori care pot aparea si nu sunt tratate. Aproape toate problemele
care pot aparea vor aparea in terminal daca este nevoie (cu cateva exceptii
unde programele continua fara a suferi modificari: input gresit, topic gresit,
etc).

# Structuri folosite si variabile
    Pentru usurinta, am apelat typedef pentru structuri precum struct
sockaddr_in, struct sockaddr si pollfd. Avem 4 structuri noi:
    - Message
    - Subscriber
    - Post
    - Forum

    Message reprezinta pachetul transmis cu datele de care ne vom folosi mereu.
Acesta este unitatea principala pentru postari si pentru reply-uri.
    Subscriber reprezinta clientii TCP conectati la server (o sa zic ca este
forum pentru ca asa l-am inteles). Un abonat poate fi online/offline (is_on),
poate avea un numar de mesaje trimis (num_mess), un fd si un id.
    Post reprezinta o postare unde pot exista reply-uri si alti abonati. Aco-
lo se poate adauga si un subiect (topic), numarul de reply-uri, numarul de a-
bonati si chiar cei care au pus reply-urile.
    Reply este un mesaj pus pe o postare si apare cand un client se aboneaza
la un topic care deja exista si adauga in el un alt mesaj. Poate fi vazut ca
un mesaj in timp ce Post este o lista mai speciala cu mesaje.
    Forum contine toate postarile si numarul de postari. Este denumit moodle
deoarece mi se pare foarte amuzant :D.
    Sunt cateva variabile globale, dar cele importante sunt server, client,
clients (pentru abonati) si cele pentru socketuri.
    p_fds contin fd-uri clientilor, fds cate am momentan. Daca:
    - fds == 0 -> primesc input din terminal
    - fds == 1 (pe server) -> UDP
    - fds == 2 (pe server) -> TCP
    - restul (pe server) -> clientii care sunt activi
    - fds == 1 (pe client) -> TCP

# Implementare server.c
    Pe langa partea comuna cu client.c, acesta are mai multe lucruri in plus.
Acesta primeste input de la clientii UDP si le baga in Forumul moodle pentru
a fi folosite mai tarziu de ei sau de alti clienti. La fiecare pas facut in
while se verifica daca este nevoie de o actualizare (e posibil ca un client
sa nu primeasca toate mesajele cand altii se aboneaza / se dezaboneaza) asa
ca ma folosesc de 2 fielduri din Post si Subscriber ca sa compar numarul de
mesaje trimise de acesta.
    Daca:
    - comanda de la tastatura -> se verifica daca e "exit\n"
    - comanda e "exit\n" -> se deconecteaza toti clientii TCP si se inchide
                            serverul
    - mesaje pe socketul UDP -> mesajele se vor adauga in Forum in functie
                                de Post sau de Reply (daca deja exista to-
                                picul, atunci el este Post si ce adaugam
                                noi este un Reply)
    - mesaje pe socketul TCP -> un client nou s-a conectat pe server si trebu-
                                ie sa ii trimitem toate informatiile despre a-
                                cesta si postarile / reply-uri din care face
                                parte
    - mesaje pe alte fd-uri -> asteptam comenzile de subscribe si unsubscribe:
                               daca un client da subscribe la un topic, se va
                               adauga un Post daca nu exista deja sau Reply da-
                               ca era deja o postare ca cea a utilizatorului

    De asemenea, se verifica daca se poate actualiza moodle-ul, si doar cei ca-
re sunt online for primi modificarile in timp real, in timp ce cei care se vor
conecta vor primi la conectare.
    Este prevazut si cazul in care se incearca doi clienti sa se conecteze pe
acelasi id si este rezolvat: clientul care exista nu pateste nimic, in timp ce
cel care a incercat sa intre peste el nu primeste conectare la server si se a-
fiseaza mesaje pe ecran conform cerintelor.

# Implementare client.c
    Pentru a evita repetarea, se folosesc multe parti de la server. Nu avem
UDP, deci se foloseste doar TCP (p_fds[0] -> STDIN si p_fds[1] -> TCP).
    Se verifica foarte bine daca comanda de executare a fost facuta cum tre-
buie, dar si daca se face conectare cum trebuie. Functiile facute special sa
anunte problemele se regasesc si in acest fisier.
    Programul astepta de la tastatura comenzi pentru a da subscribe / unsub-
scribe la un anumit topic/anumite topicuri sau comanda exit. El primeste mesa-
jele de la server (evident ca cele destinate acestuia) si le desparte pentru
a obtine informatiile cerute de pe moodle