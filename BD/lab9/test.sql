--* pasul 1 - joburile cu cei mai multi fara comision

SELECT functie, COUNT(functie) FROM angajati
WHERE comision = 0 or comision is NULL
GROUP BY functie
ORDER BY 2 DESC;

--* pasul 2 - joburile cu cei mai multi fara comision pe departamente

SELECT id_dep, functie, COUNT(functie) "0_comision" FROM angajati
WHERE comision = 0 or comision is NULL
GROUP BY id_dep, functie
ORDER BY id_dep, 3 DESC;

--* pasul 3 - departamentul cu cei mai multi fara comision
SELECT id_dep, COUNT(*) "0_comision" FROM angajati
WHERE comision = 0 OR comision IS NULL
GROUP BY id_dep
ORDER BY "0_comision" DESC;

--* pasul 4 - selectare id departament cu cei mai multi
SELECT id_dep FROM (SELECT id_dep, COUNT(*) "0_comision" FROM angajati
    WHERE comision = 0 OR comision IS NULL
    GROUP BY id_dep
    ORDER BY "0_comision" DESC)
WHERE "0_comision" = (SELECT MAX(n) FROM (SELECT id_dep, COUNT(*) n FROM angajati
    WHERE comision = 0 OR comision IS NULL
    GROUP BY id_dep
    ORDER BY "0_comision" DESC));


--* pasul 5 - rezultatul cerut

SELECT d.den_dep "Denumire Departamnt", a.nume "Nume angajat", a.functie "Job", nvl(a.comision, 0) "Comision"
FROM angajati a JOIN departamente d on a.id_dep = d.id_dep
WHERE a.id_dep = (SELECT id_dep FROM (SELECT id_dep, COUNT(*) "0_comision" FROM angajati
    WHERE comision = 0 OR comision IS NULL
    GROUP BY id_dep
    ORDER BY "0_comision" DESC)
WHERE "0_comision" = (SELECT MAX(n) FROM (SELECT id_dep, COUNT(*) n FROM angajati
    WHERE comision = 0 OR comision IS NULL
    GROUP BY id_dep
    ORDER BY "0_comision" DESC)));
