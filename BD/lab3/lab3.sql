-- exemplul 1

SELECT id_ang, nume, functie, salariu
    FROM angajati
    WHERE id_sef = &id_sef;

-- exemplul 2

SELECT nume, '&functie' functie, salariu
    FROM angajati
    WHERE functie = &functie;

-- exemplul 3

SELECT nume, functie, &salariu_anual salariu_anual
    FROM &tabel
    WHERE &nume_coloana = &valoare_coloana;

-- exemplul 4

SELECT nume, functie, &&venit_lunar venit_lunar
    FROM angajati
    WHERE &venit_lunar > 2000;

-- exemplul 5

SELECT id_ang, nume, functie, data_ang
    FROM angajati
    WHERE functie = '&1' AND data_ang > '&2'
    ORDER BY data_ang;

-- exemplul 6

ACC functie_ang char prompt 'Introdu nume angajat:';

SELECT nume, salariu, comision
    FROM angajati
    WHERE functie = '&functie_ang';

undefine functie_ang;

-- exemplul 7

ACC id_ang  char prompt 'Introduceti ecusonul angajatului:'
ACC nume    char prompt 'Introduceti numele angajatului:'
ACC functie char prompt 'Introduceti functia angajatului:'
ACC salariu char prompt 'Introduceti salariul angajatului:' hide

INSERT INTO angajati(id_ang, nume, functie, salariu)
    VALUES(&id_ang, '&nume', '&functie', &salariu);

undefine id_ang
undefine functie
undefine nume
undefine salariu

-- exemplul 8

define procent_prima = 0.15
define id_dep = 20

SELECT nume, salariu, salariu * &procent_prima prima
    FROM angajati
    WHERE id_dep = &id_dep;

undefine procent_prima
undefine id_dep

-- ex final -> metoda 1

accept id_dep number prompt 'Introduceti id departament: ';
accept venit_mediu number prompt 'Introduceti venit mediu anual: ';

SELECT nume, id_dep, &salariu_y venit_anual
    FROM angajati
    WHERE id_dep = &id_dep AND &salariu_y > &venit_mediu;

undefine id_dep;
undefine venit_mediu;

-- ex final -> metoda 2

accept id_dep number prompt 'Introduceti id departament: ';
accept venit_mediu number prompt 'Introduceti venit mediu anual: ';

define salariu_y = 12 * salariu;

SELECT nume, id_dep, &salariu_y venit_anual
    FROM angajati
    WHERE id_dep = &id_dep AND &salariu_y > &venit_mediu;

undefine id_dep;
undefine venit_mediu;
undefine salariu_y;

-- ex final -> metoda 4

accept id_dep number prompt 'Introduceti id departament: ';
accept venit_mediu number prompt 'Introduceti venit mediu anual: ';

SELECT nume, id_dep, &&salariu_y venit_anual
    FROM angajati
    WHERE id_dep = &id_dep AND &salariu_y > &venit_mediu;

undefine id_dep;
undefine venit_mediu;