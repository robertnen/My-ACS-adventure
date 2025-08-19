SELECT d.den_dep, a.functie, COUNT(a.id_ang) nr_ang
FROM angajati a NATURAL JOIN departamente d
GROUP BY d.den_dep,
    a.functie HAVING COUNT(a.id_ang) = (SELECT MAX(COUNT(id_ang)) FROM angajati
                                            GROUP BY id_dep, functie);


SELECT MAX((SELECT (COUNT(id_ang))
            FROM angajati
            WHERE id_dep = s.id_dep AND
                    functie = s.functie
            GROUP BY id_dep, functie)) max_count
FROM angajati s;


SELECT d.den_dep, a.functie, COUNT(a.id_ang) nr_ang
FROM angajati a NATURAL JOIN departamente d
GROUP BY d.den_dep,
    a.functie HAVING COUNT(a.id_ang) = (SELECT MAX((SELECT (COUNT(id_ang))
                                                FROM angajati
                                                WHERE id_dep = s.id_dep AND
                                                        functie = s.functie
                                                GROUP BY id_dep, functie)) max_count
                                        FROM angajati s);


define id_dep = 30;
SELECT d.den_dep, a.nume, a.functie, a.comision
FROM angajati a INNER JOIN departamente d
                    ON a.id_dep = d.id_dep
GROUP BY d.den_dep, a.nume, a.functie, a.comision
HAVING MAX(a.comision) IN (SELECT MAX(comision) FROM angajati
                            WHERE id_dep = &id_dep
                            GROUP BY id_dep);


SELECT a.nume, a.functie, a.data_ang, a.salariu
FROM angajati a, (SELECT id_dep, MAX(salariu) sal_max FROM angajati
                    GROUP BY id_dep) b
GROUP BY a.nume, a.functie, a.data_ang, a.salariu
HAVING a.salariu = MAX(b.sal_max)
ORDER BY a.nume;



SELECT nume Nume_ang, (SELECT nume FROM angajati WHERE id_ang = a.id_sef) Nume_sef
FROM angajati a
WHERE id_dep = 20
ORDER BY nume;


SELECT id_dep, nume, functie
FROM angajati a
WHERE id_dep IN (10, 20)
ORDER BY (SELECT COUNT(*) FROM angajati b
            WHERE a.id_dep = b.id_dep) DESC;


SELECT id_dep, nume, functie, salariu FROM angajati
WHERE salariu > SOME(SELECT DISTINCT salariu FROM angajati WHERE functie = 'SALESMAN')
ORDER BY id_dep, nume;


SELECT id_dep, nume, functie, salariu FROM angajati
WHERE salariu > ALL(SELECT DISTINCT salariu FROM angajati WHERE functie = 'SALESMAN')
ORDER BY id_dep, nume;


SELECT d.id_dep, d.den_dep FROM departamente d
WHERE EXISTS(SELECT nume FROM angajati WHERE id_dep = d.id_dep)
ORDER BY id_dep;


SELECT id_dep, id_ang, nume, functie, id_sef FROM angajati a
WHERE NOT EXISTS(SELECT id_sef FROM angajati WHERE id_ang = a.id_sef)
ORDER BY id_dep;


SELECT id_dep, id_ang, nume, functie, id_sef FROM angajati a
WHERE id_sef NOT IN (SELECT DISTINCT id_sef FROM angajati)
ORDER BY id_dep;


--* ex 1
SELECT functie, (SELECT AVG(salariu + nvl(comision, 0)) FROM angajati
                    WHERE functie = a.functie) Venit_mediu FROM angajati a;


--* ex 2
SELECT functie, sg.grade, AVG(salariu) as salariu_mediu
FROM angajati a
    JOIN salgrade sg ON a.salariu BETWEEN sg.losal AND sg.hisal
GROUP BY functie, sg.grade
HAVING avg(salariu) >= (SELECT AVG(salariu) FROM angajati a2 JOIN salgrade sg2
                                    ON a2.salariu BETWEEN sg2.losal AND sg2.hisal
                                    WHERE sg2.grade = sg.grade);


--* ex 3

--* metoda 1
SELECT a.nume, d.den_dep, a.functie, (a.salariu + NVL(comision, 0)) venit_lunar
FROM angajati a
    JOIN departamente d ON a.id_dep = d.id_dep
WHERE NOT (a.salariu + NVL(comision, 0)) < ANY(
            SELECT (b.salariu + NVL(b.comision, 0)) FROM angajati b
            WHERE b.id_dep = a.id_dep)
ORDER BY d.den_dep;


--* metoda 2
SELECT a.nume, d.den_dep, a.functie, (a.salariu + NVL(comision, 0)) venit_lunar
FROM angajati a
    JOIN departamente d ON a.id_dep = d.id_dep
WHERE (a.salariu + NVL(comision, 0)) >= ALL(
            SELECT (b.salariu + NVL(b.comision, 0)) FROM angajati b
            WHERE b.id_dep = a.id_dep)
ORDER BY d.den_dep;


--* metoda 3
SELECT a.nume, d.den_dep, a.functie, (a.salariu + NVL(comision, 0)) venit_lunar
FROM angajati a
    JOIN departamente d ON a.id_dep = d.id_dep
WHERE NOT EXISTS (SELECT 1 FROM angajati b WHERE b.id_dep = a.id_dep
                    AND (b.salariu + nvl(b.comision, 0)) > (a.salariu + NVL(a.comision, 0)))
ORDER BY d.den_dep;
