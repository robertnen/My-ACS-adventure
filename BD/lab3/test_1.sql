-- metoda 1

SELECT nume as "NUME ANGAJAT", data_ang as "DATA ANGAJARE", functie as "JOB", salariu as "Salariu vechi", comision, &salariu_nou as "SALARIU NOU"
    FROM angajati
    WHERE data_ang < (SELECT data_ang FROM angajati WHERE functie = 'PRESIDENT')
    AND (comision is null OR comision = 0);

-- metoda 2

SELECT nume as "NUME ANGAJAT", data_ang as "DATA ANGAJARE", functie as "JOB", salariu as "Salariu vechi", comision, &&salariu_nou as "SALARIU NOU"
    FROM angajati
    WHERE data_ang < (SELECT data_ang FROM angajati WHERE functie = 'PRESIDENT')
    AND (comision is null OR comision = 0);

-- metoda 2

define salariu_nou=salariu*1.10

SELECT nume as "NUME ANGAJAT", data_ang as "DATA ANGAJARE" as "JOB", functie, salariu as "Salariu vechi", comision, &salariu_nou as "SALARIU NOU"
    FROM angajati
    WHERE data_ang < (SELECT data_ang FROM angajati WHERE functie = 'PRESIDENT')
    AND (comision is null OR comision = 0);

-- metoda 5

define data_pres = SELECT data_ang FROM angajati WHERE functie = 'PRESIDENT';

SELECT nume as "NUME ANGAJAT", data_ang as "DATA ANGAJARE", functie as "JOB", salariu as "Salariu vechi", comision, &salariu_nou as "SALARIU NOU"
    FROM angajati
    WHERE data_ang < &data_pres AND (comision is null OR comision = 0);
