-- --* sefi de departament
-- SELECT id_ang, nume, id_dep FROM angajati a
-- WHERE id_ang IN (SELECT id_sef FROM angajati);

-- --* salarii pe un departament
-- SELECT salariu, a.id_dep FROM angajati a
-- JOIN departamente d ON a.id_dep = d.id_dep
-- ORDER BY a.id_dep;

--

-- SELECT AVG(salariu), id_dep FROM (SELECT salariu, a.id_dep id_dep FROM angajati a
-- JOIN departamente d ON a.id_dep = d.id_dep)
-- GROUP BY id_dep
-- ORDER BY id_dep;

--* salariu mediu departament
CREATE VIEW salariu_mediu AS
    SELECT AVG(salariu) AS salariu_med, id_dep AS id_dep
    FROM angajati
    GROUP BY id_dep;

--* angajatii cu salariu mai mare decat salariul mediu pe departament
CREATE VIEW angajati_peste AS
    SELECT a.id_ang, a.nume, a.salariu, a.id_dep, s.salariu_med
    FROM angajati a
    JOIN salariu_mediu s ON a.id_dep = s.id_dep
    WHERE a.salariu > s.salariu_med;

--* departamentul cu cei mai multi angajati care au peste salariul mediu
CREATE VIEW dep_peste AS
    SELECT id_dep
    FROM angajati_peste
    GROUP BY id_dep
    ORDER BY COUNT(*) DESC;

SELECT a.id_dep, s.salariu_med, a.nume AS nume_angajat, a.salariu AS salariu_angajat
FROM angajati_peste a
JOIN dep_peste d ON a.id_dep = d.id_dep, salariu_mediu s;



CREATE VIEW sef_nou_an_1 AS
SELECT EXTRACT(YEAR FROM MAX(data_ang)) AS an_max
FROM angajati
WHERE id_ang IN (SELECT DISTINCT id_sef FROM angajati WHERE id_sef IS NOT NULL);


CREATE VIEW salariu_mediu_pe_dep_1 AS
SELECT id_dep, AVG(salariu) AS salariu_mediu_dep
FROM angajati
GROUP BY id_dep;


CREATE VIEW angajati_peste_medie_an_sef_1 AS
SELECT a.id_ang, a.nume, a.salariu, a.id_dep, s.salariu_mediu_dep
FROM angajati a
JOIN salariu_mediu_pe_dep_1 s ON a.id_dep = s.id_dep
JOIN sef_nou_an y ON EXTRACT(YEAR FROM a.data_ang) = y.an_max
WHERE a.salariu > s.salariu_mediu_dep;

CREATE VIEW departament_maxim_1 AS
SELECT id_dep
FROM angajati_peste_medie_an_sef_1
GROUP BY id_dep
ORDER BY COUNT(*) DESC
FETCH FIRST 1 ROWS ONLY;

SELECT a.id_dep, a.salariu_mediu_dep, a.nume AS nume_angajat, a.salariu AS salariu_angajat
FROM angajati_peste_medie_an_sef_1 a
JOIN departament_maxim_1 d ON a.id_dep = d.id_dep;

