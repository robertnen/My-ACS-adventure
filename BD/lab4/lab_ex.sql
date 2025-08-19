SELECT nume, comision, data_ang, id_dep
FROM angajati_
WHERE (comision = 0 OR comision IS NULL) AND
    data_ang < '1-JAN-1982';

SELECT nume, salariu, id_sef, functie, id_dep
FROM angajati_
WHERE salariu >= 3000 AND (id_sef = 0 OR id_sef IS NULL)
ORDER BY id_dep;

SELECT nume, functie, salariu*12 AS "Venit anual"
FROM angajati_
WHERE LOWER(functie) != 'manager' AND id_dep = &id_dept;

SELECT d.den_dep as "Departament", a.nume, a.data_ang, a.salariu
FROM angajati_ a, departamente_ d
WHERE a.data_ang LIKE '%81' AND (d.id_dep = &dep_1 OR d.id_dep = &dep_2);