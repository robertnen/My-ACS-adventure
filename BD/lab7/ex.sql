SELECT to_char(SysDate, 'DD-MM-YYYY') data_curenta
FROM dual;

SELECT to_date('15112006', 'MM-YYYY') data_ex
FROM dual;

SELECT to_char(-10000, '$999999.99MI') valoare
FROM dual;

SELECT to_number('$10000.00-', '$999999.99MI') valoare
FROM dual;


SELECT nume, to_char(data_ang, 'dd-mm-yyyy') data_ang
FROM angajati
WHERE to_char(data_ang, 'YYYY') LIKE '1982';

SELECT nume, to_char(data_ang, 'dd-mm-yyyy') data_ang
FROM angajati
WHERE to_date(to_char(data_ang, 'YYYY'), 'YYYY') =
      to_date(to_char(1982), 'YYYY');

SELECT nume, to_char(data_ang, 'dd-mm-yyyy') data_ang
FROM angajati
WHERE to_number(to_char(data_ang, 'YYYY')) = 1982;


COLUMN numar FORMAT 99999
SELECT 123.14 numar FROM dual;

COLUMN numar FORMAT 999.99
SELECT 123.14 numar FROM dual;

COLUMN numar FORMAT $999.99
SELECT 123.14 numar FROM dual;

COLUMN numar FORMAT 00999.99
SELECT 123.14 numar FROM dual;
SELECT 0.14 numar FROM dual;


SELECT greatest(23, 12, 34, 77, 89, 52) gr
FROM dual;

SELECT least(23, 12, 34, 77, 89, 52) gr
FROM dual;

SELECT greatest('15-JAN-1985', '23-AUG-01') gr
FROM dual;

SELECT least('15-JAN-1985', '23-AUG-01') gr
FROM dual;


SELECT nume, functie, salariu,
    decode(functie, 'MANAGER', salariu * 1.25,
                    'ANALYST', salariu * 1.24,
                    salariu / 4) prima
FROM angajati
WHERE id_dep = 20
ORDER BY functie;

SELECT nume, functie, salariu,
    to_char(data_ang, 'YYYY') an_ang,
    decode (sign(data_ang - to_date('1-JAN-1982')),
        -1, salariu * 1.25,
        salariu * 1.1) prima
FROM angajati
WHERE id_dep = 20
ORDER BY functie;


SELECT
    case Lower(sediu)
        WHEN 'new york' THEN 1
        WHEN 'dallas' THEN 2
        WHEN 'chicago' THEN 3
        WHEN 'boston' THEN 4
    end cod_dep
FROM departamente;


SET null NULL;
SELECT nume, comision, nvl(comision, 0) nvl_com,
        salariu + comision "Sal + Com",
        salariu + nvl(comision, 0) "Sal + Nvl_com"
FROM angajati
WHERE id_dep = 30;
SET null '';

SELECT USER FROM dual;


SELECT avg(salariu) salariu FROM angajati;
SELECT avg(ALL salariu) salariu FROM angajati;
SELECT avg(DISTINCT salariu) salariu FROM angajati;


SELECT id_dep, avg(salariu) FROM angajati
GROUP BY id_dep
ORDER BY 1;

SELECT id_dep, avg(salariu + nvl(comision, 0)) FROM angajati
GROUP BY id_dep
having avg(salariu + nvl(comision, 0)) > 2000;


SELECT id_dep, count(*) nr_ang, count(salariu) count,
        count(all salariu) count_all, count(DISTINCT salariu) count_distinct
FROM angajati
GROUP BY id_dep
ORDER BY 1;

SELECT id_dep, count(functie) count, count(DISTINCT functie) count_distinct
FROM angajati
GROUP BY id_dep
HAVING count(DISTINCT functie) >= 2
ORDER BY 1;


SELECT d.den_dep,
    min(a.salariu) sal_min,
    min(DISTINCT a.salariu) sal_min_d,
    max(a.salariu) sal_max,
    max(DISTINCT a.salariu) sal_max_d,
    sum(a.salariu) sal_sum,
    sum(DISTINCT a.salariu) sal_sum_d
FROM angajati a NATURAL JOIN departamente d
GROUP BY d.den_dep
ORDER BY d.den_dep;


SELECT id_dep, VARIANCE(salariu) sal_varstd,
        VARIANCE(DISTINCT salariu) sal_varstd_d,
        STDDEV(salariu) sal_devstd,
        STDDEV(DISTINCT salariu) sal_devstd_d,
        STDDEV(comision) com_devstd
FROM angajati
GROUP BY id_dep
ORDER BY 1;


--! ex 1 si 2
SELECT a1.id_sef, a2.nume, count(a1.id_sef) "Numar subalterni", d.den_dep,
    min(a1.salariu) "Salariu minim",
    avg(a1.salariu) "Salariu mediu",
    max(a1.salariu) "Salariu maxim"
FROM angajati a1, angajati a2, departamente d
WHERE a1.id_sef = a2.id_ang AND a2.id_dep = d.id_dep
GROUP BY a1.id_sef, a2.nume, d.den_dep
ORDER BY 1;


SELECT a1.id_sef, a2.nume "Nume sef", count(a1.id_sef) "Numar subalterni",
    d.den_dep,
    min(a1.salariu) salariu_minim,
    avg(a1.salariu) salariu_mediu,
    max(a1.salariu) salariu_maxim
FROM angajati a1 JOIN angajati a2 ON a1.id_sef = a2.id_ang
                        JOIN departamente d ON a2.id_dep = d.id_dep
GROUP BY a1.id_sef, a2.nume, d.den_dep
ORDER BY a1.id_sef;


SELECT Initcap(Lower(nume)), Lower(d.den_dep), to_char(data_ang, 'MM-YYYY') "Data ang",
FROM angajati a1 JOIN angajati a2 ON a1.id_sef = a2.id_ang
     JOIN departamente d ON a1.id_dep = d.id_dep
GROUP BY a1.id_sef, a2.nume, d.den_dep
ORDER BY 1;


SELECT
    INITCAP(a.nume) AS nume_angajat,
    LOWER(d1.den_dep) AS departament_angajat,
    TO_CHAR(a.data_angajare, 'MM-YYYY') AS luna_an_angajare,
    
    CASE grad_salarial IN (2, 4) AND EXTRACT(YEAR FROM a.data_angajare) = EXTRACT(YEAR FROM sef.data_angajare) THEN
            CASE 
                WHEN grad_salarial = 2 THEN a.salariu * SQRT(:c * LOG(2, MONTHS_BETWEEN(SYSDATE, a.data_angajare)))
                WHEN grad_salarial = 4 THEN a.salariu * SQRT(:c * LOG(3, MONTHS_BETWEEN(SYSDATE, a.data_angajare)))
            END
        ELSE 0
    END AS prima,
    
    grad_salarial,
    
    INITCAP(sef.nume) AS nume_sef,
    LOWER(d2.den_dep) AS departament_sef

FROM (
    SELECT *,
        CASE 
            WHEN salariu < 3000 THEN 1
            WHEN salariu < 5000 THEN 2
            WHEN salariu < 7000 THEN 3
            ELSE 4
        END AS grad_salarial
    FROM angajati
) a

LEFT JOIN angajati sef ON a.id_sef = sef.id_ang
LEFT JOIN departamente d1 ON a.id_dep = d1.id_dep
LEFT JOIN departamente d2 ON sef.id_dep = d2.id_dep

ORDER BY INITCAP(a.nume);
