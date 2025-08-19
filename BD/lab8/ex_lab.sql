--* sefii de departament

SELECT UNIQUE a1.nume, a1.id_dep, a2.id_dep
FROM angajati a1, angajati a2
WHERE (a1.id_sef = a2.id_ang
        AND a1.id_sef = (SELECT id_ang
            FROM angajati WHERE lower(functie) = 'president')) AND NOT a1.id_dep = a2.id_dep;

--* salariu mediu subalterni

SELECT UNIQUE a1.nume, (SELECT avg(b.salariu + nvl(b.comision, 0))
        FROM angajati b WHERE b.id_sef = a1.id_ang) "Salariu mediu subalterni",
FROM angajati a2, angajati a1
WHERE (a1.id_sef = a2.id_ang
        OR a1.id_sef = (SELECT id_ang
            FROM angajati WHERE lower(functie) = 'president')) AND NOT a1.id_dep = a2.id_dep;

--* venit sef + denumire departament

SELECT UNIQUE d.den_dep, a1.nume, a1.salariu + nvl(a1.comision, 0) "Venit sef",
        (SELECT avg(b.salariu + nvl(b.comision, 0))
            FROM angajati b WHERE b.id_sef = a1.id_ang) "Salariu mediu subalterni"
FROM angajati a2, angajati a1, departamente d
WHERE (a1.id_sef = a2.id_ang
        OR a1.id_sef = (SELECT id_ang
            FROM angajati WHERE lower(functie) = 'president'))
                AND NOT a1.id_dep = a2.id_dep AND d.id_dep = a1.id_dep;


--* sefii de departament
SELECT a1.nume, a1.salariu + nvl(a1.comision, 0) "Venit sef"
FROM angajati a1
WHERE a1.salariu > (SELECT avg(salariu) FROM angajati a2 WHERE a2.id_sef = a1.id_ang);

--* final
SELECT a1.nume, a1.salariu + nvl(a1.comision, 0) "Venit sef", d.den_dep
FROM angajati a1
WHERE a1.salariu > (SELECT avg(salariu) FROM angajati a2 WHERE a2.id_sef = a1.id_ang);

select
	d.den_dep as denumire_departament,
	a.nume as nume_sef,
	a.salariu+nvl(a.comision,0) as venit_sef,
	(select avg(salariu) from angajati b where b.id_sef = a.id_ang) as venit_mediu_subaltern
from angajati a natural join departamente d
where a.salariu > (select avg(salariu) from angajati b where b.id_sef = a.id_ang);