SELECT UNIQUE a1.nume "Nume angajat", a1.functie "Jon",
        a1.data_ang "Data angajarii",
        CASE
            WHEN to_char(a1.data_ang, 'YYYY') < '1981' THEN 'Vechime Mare'
            WHEN to_char(a1.data_ang, 'YYYY') = '1981' THEN 'Vechime Medie'
            WHEN to_char(a1.data_ang, 'YYYY') > '1981' THEN 'Vechime Mica'
        END "Vechime",
        count(a1.id_sef) "Numar subalterni", d.den_dep
FROM angajati a1, angajati a2, departamente d
WHERE (a1.id_ang = a2.id_sef OR a2.id_ang = a1.id_sef) AND a1.id_dep = d.id_dep AND Lower(d.den_dep) = 'research'
GROUP BY a1.nume, a1.functie, a1.data_ang, a2.id_sef, d.den_dep
ORDER BY 1;


SELECT DISTINCT a1.nume "Nume angajat", a1.functie "Jon",
        a1.data_ang "Data angajarii",
        CASE
            WHEN Trunc(a1.data_ang, 'Year') < '01-JAN-1981' THEN 'Vechime Mare'
            WHEN Trunc(a1.data_ang, 'Year') = '01-JAN-1981' THEN 'Vechime Medie'
            WHEN Trunc(a1.data_ang, 'Year') > '01-JAN-1981' THEN 'Vechime Mica'
        END "Vechime",
        count(a1.id_sef) "Numar subalterni", d.den_dep
FROM angajati a1, angajati a2, departamente d
WHERE (a1.id_ang = a2.id_sef OR a2.id_ang = a1.id_sef) AND a1.id_dep = d.id_dep AND Lower(d.den_dep) = 'research'
GROUP BY a1.nume, a1.functie, a1.data_ang, a2.id_sef, d.den_dep
ORDER BY 1;



SELECT
    INITCAP(a.nume) "Nume angajat",
    a.functie "Job",
    a.data_ang "Data angajarii",
    CASE
        WHEN Trunc(a.data_ang, 'Year') < '01-JAN-1981' THEN 'Vechime Mare'
        WHEN Trunc(a.data_ang, 'Year') = '01-JAN-1981' THEN 'Vechime Medie'
        ELSE 'Vechime Mica'
    END AS "Vechime",
    (
        SELECT COUNT(*) FROM angajati s
        WHERE s.id_sef = a.id_ang
    ) "Numar subalterni"
FROM angajati a
JOIN departamente d ON a.id_dep = d.id_dep
WHERE LOWER(d.den_dep) = 'research'
ORDER BY a.nume;


SELECT
    INITCAP(a.nume) "Nume angajat",
    a.functie "Job",
    a.data_ang "Data angajarii",
    CASE
        WHEN to_char(a.data_ang, 'YYYY') < '1981'  THEN 'Vechime Mare'
        WHEN to_char(a.data_ang, 'YYYY') = '1981' THEN 'Vechime Medie'
        ELSE 'Vechime Mica'
    END AS "Vechime",
    (
        SELECT COUNT(*) FROM angajati s
        WHERE s.id_sef = a.id_ang
    ) "Numar subalterni"
FROM angajati a
JOIN departamente d ON a.id_dep = d.id_dep
WHERE LOWER(d.den_dep) = 'research'
ORDER BY a.nume;

