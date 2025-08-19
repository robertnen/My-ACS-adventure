--* pasul 1: departamentul lui scott

SELECT id_dep FROM angajati
WHERE lower(nume) = 'scott';


--* pasul 2: grila salariala

SELECT g.grad "Grad", a.id_dep, a.nume, a.salariu
FROM angajati a
    JOIN grila_salariu g ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
ORDER BY 1 DESC;


--* pasul 3: grila salariu - cati intra in fiecare prag

SELECT g.grad "Grad", COUNT(*) "Numar Angajati"
FROM angajati a
    JOIN grila_salariu g ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
    GROUP BY g.grad
ORDER BY "Numar Angajati" DESC;


--* pasul 5: rezultatul final + crearea tabelei

CREATE TABLE angajati_ceruti_ AS
    SELECT d.den_dep "Denumire departament", a.nume "Nume angajat", a.salariu "Salariu", g.grad "Grad Salariu"
    FROM angajati a
        JOIN departamente d ON a.id_dep = d.id_dep
        JOIN grila_salariu g ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
            WHERE a.id_dep = (SELECT id_dep FROM angajati
                                WHERE lower(nume) = 'scott')
    AND g.grad = (SELECT "Grad"
                    FROM (SELECT g.grad "Grad", COUNT(*) "Numar angajati"
                        FROM angajati a
                        JOIN grila_salariu g ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
                        GROUP BY g.grad
                        ORDER BY "Numar angajati" DESC)
                    WHERE ROWNUM = 1);