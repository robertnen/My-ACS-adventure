SELECT
    nume AS "Nume angajat",
    data_ang as "Data angajare",
    comision as "Comision Angajat",
    '&1' AS "Data angajare presedinte",
    salariu as "Salariu angajat",
    &2 AS "Salariu director",
    salariu*1.1 as "Prima"
FROM angajati_
WHERE salariu < &2 AND
    data_ang LIKE '%81' AND (comision = 0 OR comision IS NULL);
