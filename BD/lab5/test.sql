SELECT a1.nume "Nume subaltern", d1.den_dep "Denumire departament", a1.data_ang "Data angajare",
    a1.functie "Functie subaltern", a2.nume "Nume sef", d2.den_dep "Denumire departament sef",
    a2.data_ang "Data ang sef", a2.functie "Functie sef"
FROM angajati a1, angajati a2, departamente d1, departamente d2
WHERE a1.id_sef = a2.id_ang AND
      a1.functie != 'MANAGER' AND
      a1.data_ang > a2.data_ang AND
      a1.id_dep = d1.id_dep AND
      a2.id_dep = d2.id_dep AND
      (a1.id_dep = 10 OR a1.id_dep = 30)
ORDER BY 1;


SELECT a1.nume "Nume subaltern", d1.den_dep "Denumire departament", a1.data_ang "Data angajare",
    a1.functie "Functie subaltern", a2.nume "Nume sef", d2.den_dep "Denumire departament sef",
    a2.data_ang "Data ang sef", a2.functie "Functie sef"
FROM angajati a1 INNER JOIN angajati a2
                        INNER JOIN departamente d2 ON a2.id_dep = d2.id_dep
                        ON a1.id_sef = a2.id_ang AND a1.functie != 'MANAGER' AND a1.data_ang > a2.data_ang
    INNER JOIN departamente d1
    ON a1.id_dep = d1.id_dep
WHERE (a1.id_dep = 10 OR a1.id_dep = 30)
ORDER BY 1;


SELECT a1.nume "Nume subaltern", d1.den_dep "Denumire departament", a1.data_ang "Data angajare",
    a1.functie "Functie subaltern", a2.nume "Nume sef", d2.den_dep "Denumire departament sef",
    a2.data_ang "Data ang sef", a2.functie "Functie sef"
FROM angajati a1 JOIN angajati a2
                        ON a1.id_sef = a2.id_ang AND a1.functie != 'MANAGER' AND a1.data_ang > a2.data_ang
    ,departamente d1, departamente d2
WHERE a1.id_dep = d1.id_dep AND
      a2.id_dep = d2.id_dep AND
      (a1.id_dep = 10 OR a1.id_dep = 30)
ORDER BY 1;