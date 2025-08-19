SELECT id_dep, nume, functie, salariu
FROM angajati
WHERE salariu = (SELECT max(salariu) FROM angajati);

SELECT id_dep, nume, functie, salariu
FROM angajati
WHERE
    NOT id_dep = 20 AND
    functie IN (SELECT functie FROM angajati
        WHERE id_dep = 20)
ORDER BY functie;

SELECT nume, functie, data_ang
FROM angajati
WHERE data_ang NOT IN (SELECT DISTINCT(data_ang)
                FROM angajati
                WHERE to_char(data_ang, 'MON')
                    IN ('DEC', 'JAN', 'FEB'))
ORDER BY nume;

SELECT den_dep, nume, salariu
FROM angajati
    NATURAL JOIN departamente
WHERE salariu IN
    (SELECT max(salariu) FROM angajati
        GROUP BY id_dep)
ORDER BY den_dep;

SELECT id_dep, nume, functie, data_ang
FROM angajati
WHERE (to_char(data_ang, 'YYYY'), functie) IN
    (SELECT to_char(data_ang, 'YYYY'), functie FROM angajati
    WHERE lower(nume) = 'jones');

SELECT id_dep, nume, salariu
FROM angajati
WHERE (id_dep, salariu + nvl(comision, 0)) IN
    (SELECT id_dep, min(salariu + nvl(comision, 0))
        FROM angajati GROUP BY id_dep)
ORDER BY id_dep;

SELECT nume, functie, data_ang, salariu
FROM angajati
WHERE salariu > (SELECT max(salariu)
                    FROM angajati WHERE id_dep =
                            (SELECT id_dep FROM departamente
                                WHERE lower(den_dep) = 'sales'));

SELECT a.id_dep, a.nume, a.functie, a.salariu
FROM angajati a
WHERE a.salariu > (SELECT AVG(b.salariu) FROM angajati b
                    WHERE b.id_dep = a.id_dep)
ORDER BY a.id_dep;

UPDATE angajati a
SET (a.salariu, a.comision) =
    (SELECT a.salariu + avg(b.salariu) * 0.1, avg(b.comision)
        FROM angajati b
        WHERE b.id_dep = a.id_dep)
WHERE data_ang <= '1-JUN-81';

SELECT b.id_dep, a.den_dep, b.max_sal_dep FROM
    departamente a,
    (SELECT id_dep, max(salariu) max_sal_dep
        FROM angajati GROUP BY id_dep) b
WHERE a.id_dep = b.id_dep
ORDER BY b.id_dep;

SELECT b.id_dep, a.den_dep, b.max_sal_dep FROM
    departamente a INNER JOIN
    (SELECT id_dep, max(salariu) max_sal_dep
        FROM angajati GROUP BY id_dep) b
    ON a.id_dep = b.id_dep
ORDER BY b.id_dep;

--? exercitii
--* metoda 1

SELECT a.nume, d.den_dep, a.salariu
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep
    AND a.salariu = (SELECT min(salariu) FROM angajati WHERE id_dep = a.id_dep);

--* metoda 2

SELECT a.nume, d.den_dep, a.salariu
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep
    AND (a.salariu, a.id_dep) IN (SELECT min(salariu) FROM angajati WHERE id_dep = a.id_dep);

--* metoda 3

SELECT a.nume, d.den_dep, a.salariu
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep
    AND (a.salariu, a.id_dep) IN
        (SELECT min(salariu), id_dep FROM angajati HAVING id_dep = a.id_dep GROUP BY id_dep);

--* metoda 4
SELECT a.nume, d.den_dep, b.min_salariu
FROM angajati a, departamente d,
    (SELECT min(salariu) min_salariu, id_dep FROM angajati
        GROUP BY id_dep) b
WHERE a.id_dep = d.id_dep AND a.salariu = b.min_salariu;