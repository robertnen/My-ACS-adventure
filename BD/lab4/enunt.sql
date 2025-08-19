-- sa se scrie o cerere sql care face o lista cu
-- primele acordate angajatilor
-- dupa urmatoarele criterii
-- 1. trebuie sa aiba salariul mai mic decat cel
-- mai mic salariu de director
-- 2. sa se fi angajat in acelasi an cu presedintele
-- 3. sa nu fi primit comision

-- Prima este de 10% din salariu.
-- Antetul listei:
-- Nume angajat, Data angajare, Comision angajat,
-- Data angajare Presedinte, Salariu angajat,
-- Salariu director, Prima

-- Prin mai multe metode

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    (SELECT data_ang FROM angajati_ WHERE functie='PRESIDENT') AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    (SELECT MIN(salariu) FROM angajati_ WHERE functie='MANAGER') AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < (SELECT MIN(salariu) FROM angajati_ WHERE functie='MANAGER') AND
    data_ang LIKE '%81' AND (comision = 0 OR comision IS NULL);

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang LIKE '%81' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &&salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang LIKE '%81' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;


ACC data_presedinte char prompt 'Introduceti data presedintelui:'
ACC salariu_manager char prompt 'Introduceti cel mai mic salariu:'

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang LIKE '%81' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;


-- altfel


SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    (SELECT data_ang FROM angajati_ WHERE functie='PRESIDENT') AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    (SELECT MIN(salariu) FROM angajati_ WHERE functie='MANAGER') AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < (SELECT MIN(salariu) FROM angajati_ WHERE functie='MANAGER') AND
    data_ang BETWEEN '1-JAN-1981' AND '31-DEC-1981' AND (comision = 0 OR comision IS NULL);

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang BETWEEN '1-JAN-1981' AND '31-DEC-1981' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &&salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang BETWEEN '1-JAN-1981' AND '31-DEC-1981' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;


ACC data_presedinte char prompt 'Introduceti data presedintelui:'
ACC salariu_manager char prompt 'Introduceti cel mai mic salariu:'

SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&data_presedinte' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &salariu_manager AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &salariu_manager AND
    data_ang BETWEEN '1-JAN-1981' AND '31-DEC-1981' AND (comision = 0 OR comision IS NULL);

undefine data_presedinte;
undefine salariu_manager;
