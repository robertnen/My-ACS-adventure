-- cross join
SELECT nume, functie, den_dep
FROM angajati, departamente
WHERE functie = 'ANALYST';

SELECT nume, functie, den_dep
FROM angajati CROSS JOIN departamente
WHERE functie = 'ANALYST';

--? inner join

-- equi-join
--* metoda 1
SELECT a.id_dep, d.den_dep, a.nume, a.functie
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep AND a.id_dep = 10
ORDER BY 3;

SELECT angajati.id_dep, departamente.den_dep, angajati.nume, angajati.functie
FROM angajati, departamente
WHERE angajati.id_dep = departamente.id_dep AND angajati.id_dep = 10
ORDER BY 3;

--* metoda 2
SELECT a.id_dep, d.den_dep, a.nume, a.functie
FROM angajati a INNER JOIN departamente d
                ON a.id_dep = d.id_dep
WHERE a.id_dep = 10
ORDER BY 3;

--* metoda 3
SELECT id_dep, d.den_dep, a.nume, a.functie
FROM angajati a INNER JOIN departamente d
                USING(id_dep)
WHERE id_dep = 10
ORDER BY 3;

-- natural join
SELECT id_dep, den_dep, nume, functie
FROM angajati NATURAL JOIN departamente
WHERE id_dep = 10
ORDER BY 3;

-- non equi-join
SELECT a.nume, a.salariu, g.grad
FROM angajati a, grila_salariu g
WHERE a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
      AND a.id_dep = 20;

SELECT a.nume, a.salariu, g.grad
FROM angajati a INNER JOIN grila_salariu g
                ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
WHERE a.id_dep = 20;

--! ex 5
SELECT a.nume, a.salariu, g.grad, d.den_dep
FROM angajati a, grila_salariu g, departamente d
WHERE
    a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
    AND d.id_dep = a.id_dep
    AND a.id_dep = 20
ORDER BY 3, 1;

SELECT a.nume, a.salariu, g.grad, d.den_dep
FROM angajati a
    INNER JOIN grila_salariu g
            ON a.salariu BETWEEN g.nivel_inf AND g.nivel_sup
    INNER JOIN departamente d
            ON d.id_dep = a.id_dep
where a.id_dep = 20
ORDER BY 3, 1;

-- self join
--! ex 6
SELECT a1.nume "Nume angajat", a1.functie "Functie angajat", a2.nume "Nume sef", a2.functie "Functie sef"
FROM angajati a1, angajati a2
WHERE a1.id_sef = a2.id_ang AND a1.id_dep = 10;

SELECT a1.nume "Nume angajat", a1.functie "Functie angajat", a2.nume "Nume sef", a2.functie "Functie sef"
FROM angajati a1 INNER JOIN angajati a2
                         ON a1.id_sef = a2.id_ang
WHERE a1.id_dep = 10;

-- outer join
-- left outer join
SELECT d.id_dep, d.den_dep, a.nume, a.functie
FROM departamente d, angajati a
WHERE d.id_dep = a.id_dep(+)
ORDER BY a.id_dep;

SELECT d.id_dep, d.den_dep, a.nume, a.functie
FROM departamente d LEFT OUTER JOIN angajati a
                                 ON d.id_dep = a.id_dep(+)
ORDER BY a.id_dep;

--! ex 9
SELECT a.nume, a.salariu, g.grad
FROM grila_salariu g
    FULL OUTER JOIN angajati a
                 ON a.salariu*2 BETWEEN g.nivel_inf AND g.nivel_sup
ORDER BY a.nume;

--! ex 10
SELECT d.den_dep, a.nume, a.salariu, g.grad
FROM grila_salariu g
    FULL OUTER JOIN angajati a
            RIGHT OUTER JOIN departamente d
                          ON d.id_dep = a.id_dep
                 ON a.salariu*2 BETWEEN g.nivel_inf AND g.nivel_sup
ORDER BY d.den_dep, a.nume, g.grad;

SELECT d.den_dep, a.nume, a.salariu, g.grad
FROM angajati a
    FULL OUTER JOIN grila_salariu g
                 ON a.salariu*2 BETWEEN g.nivel_inf AND g.nivel_sup
    FULL OUTER JOIN departamente d
                 ON d.id_dep = a.id_dep
ORDER BY d.den_dep, a.nume, g.grad;

--! ex 11
SELECT id_dep, nume, functie, salariu
FROM angajati
WHERE id_dep = 10
UNION
SELECT id_dep, nume, functie, salariu
FROM angajati
WHERE id_dep = 30;

--! ex 12
SELECT id_dep, nume, 'are salariul' are, salariu sal_com
FROM angajati
WHERE id_dep = 10;
UNION
SELECT id_dep, nume, 'are comisionul' are, nvl(comision, 0) sal_com
FROM angajati
WHERE id_dep = 30;

--! ex 13
SELECT functie FROM angajati WHERE id_dep = 10
UNION ALL
SELECT functie FROM angajati WHERE id_dep = 30;

--! ex 14
SELECT functie, nvl(comision, 0) comision
FROM angajati WHERE id_dep = 10
INTERSECT
SELECT functie, nvl(comision, 0) comision
FROM angajati WHERE id_dep = 20
INTERSECT
SELECT functie, nvl(comision, 0) comision
FROM angajati WHERE id_dep = 30;

--! ex 15
SELECT functie
FROM angajati
WHERE id_dep = 10
MINUS
SELECT functie
FROM angajati
WHERE id_dep = 30;