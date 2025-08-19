--* salariu mediu dep
SELECT AVG(salariu), id_dep FROM angajati
GROUP BY id_dep;


--* angajatii care au salariu mai mare
SELECT nume, salariu FROM angajati a
    JOIN (SELECT AVG(salariu) salariu_mediu, id_dep FROM angajati
            GROUP BY id_dep) b
    ON a.id_dep = b.id_dep
WHERE a.salariu > b.salariu_mediu;


--* cate salarii peste medie are fiecare departament
SELECT id_dep, COUNT(*) nr_angajati FROM (
    SELECT a.id_dep FROM angajati a JOIN
        (SELECT AVG(salariu) salariu_mediu, id_dep FROM angajati
            GROUP BY id_dep) b
    ON a.id_dep = b.id_dep
    WHERE a.salariu > b.salariu_mediu
) GROUP BY id_dep;


--* luam departamentul cerut
SELECT id_dep FROM (SELECT id_dep, COUNT(*) nr_angajati FROM (
        SELECT a.id_dep FROM angajati a JOIN
            (SELECT AVG(salariu) salariu_mediu, id_dep FROM angajati
                GROUP BY id_dep) b
        ON a.id_dep = b.id_dep
        WHERE a.salariu > b.salariu_mediu
    ) GROUP BY id_dep)
WHERE nr_angajati = (SELECT MAX(n) FROM
    (SELECT COUNT(*) n FROM (
        SELECT a.id_dep FROM angajati a JOIN
        (SELECT AVG(salariu) salariu_mediu, id_dep FROM angajati
            GROUP BY id_dep) b ON a.id_dep = b.id_dep
        WHERE a.salariu > b.salariu_mediu
    ) GROUP BY id_dep));


--* rezultatul cerut
SELECT a.id_dep, b.salariu_mediu, a.nume nume_angajat, a.salariu salariu_angajat
FROM angajati a
JOIN (
    SELECT id_dep, AVG(salariu) salariu_mediu
    FROM angajati
    GROUP BY id_dep
) b ON a.id_dep = b.id_dep
WHERE a.salariu > b.salariu_mediu
    AND a.id_dep = (
        SELECT id_dep
        FROM (
            SELECT id_dep, COUNT(*) nr_angajati
            FROM (
                SELECT a.id_dep
                FROM angajati a
                JOIN (
                    SELECT id_dep, AVG(salariu) salariu_mediu
                    FROM angajati
                    GROUP BY id_dep) b ON a.id_dep = b.id_dep
                WHERE a.salariu > b.salariu_mediu)
            GROUP BY id_dep)
        WHERE nr_angajati = (
            SELECT MAX(n)
            FROM (
                SELECT COUNT(*) n
                FROM (
                    SELECT a.id_dep
                    FROM angajati a
                    JOIN (
                        SELECT id_dep, AVG(salariu) salariu_mediu
                        FROM angajati
                        GROUP BY id_dep) b ON a.id_dep = b.id_dep
                    WHERE a.salariu > b.salariu_mediu)
            GROUP BY id_dep)));
