SELECT nume  as "NUME ANGAJAT", data_ang as "DATA ANGAJARE", functie as "JOB", salariu as "Salariu vechi", comision, &1 as "SALARIU NOU"
    FROM angajati
    WHERE data_ang < (SELECT data_ang FROM angajati WHERE functie = 'PRESIDENT')
    AND (comision is null OR comision = 0);