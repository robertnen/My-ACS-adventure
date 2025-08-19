SELECT SIGN(-12) FROM dual;
SELECT ABS (-12) FROM dual;
SELECT CEIL (14.2) FROM dual;

DEFINE pi = '(SELECT asin(1)*2 FROM dual)'

SELECT SIN(30*&pi/180) sin FROM dual;
SELECT COS(60*&pi/180) cos FROM dual;
SELECT TAN (135*&pi/180) tan FROM dual;

SELECT SINH(1) sinh FROM dual;
SELECT COSH(0) cosh FROM dual;
SELECT TANH (0.5) tanh FROM dual;
SELECT ASIN(0.5) asin FROM dual;
SELECT ACOS(0) acos FROM dual;
SELECT ATAN(1) atan FROM dual;
SELECT EXP(4) exp FROM dual;
SELECT POWER(3, 2) power FROM dual;
SELECT SQRT(9) sqrt FROM dual;
SELECT LN(95) In FROM dual;
SELECT LOG(10, 100) log FROM dual;
SELECT MOD (14, 5) mod FROM dual;
SELECT ROUND(15.193, 1) FROM dual;
SELECT ROUND(15.193) FROM dual;
SELECT ROUND(15.193, -1) FROM dual;
SELECT TRUNC(15.193, 1) FROM dual;
SELECT TRUNC(15.193) FROM dual;
SELECT TRUNC(15.193, -1) FROM dual;


SELECT CHR(75) FROM dual; -- k

SELECT CONCAT(CONCAT(nume, ' este '), functie) ANG_FUNC FROM angajati
WHERE id_ang = 7839;

SELECT InitCap(nume) ex_initcap FROM angajati
where id_ang = 7839;

SELECT Replace('Jack si Jue', 'J', 'Bl') ex_replace FROM dual;

SELECT RPAD(nume, 10, '*') EX_RPAD FROM angajati
WHERE id_dep = 10;

SELECT LPAD(nume, 10, '*') EX_RPAD FROM angajati
WHERE id_dep = 10;

SELECT Rtrim('Popescu', 'scu') FROM dual;
SELECT Substr('Popescu', 2, 3) FROM dual;

SELECT Instr('Protopopescu', 'op', 3, 2) FROM dual;

SELECT Length('analyst') FROM dual;

SELECT Translate('Oana are mere', '0m', ' p') FROM dual;
SELECT Translate('Oana0are0mere', '0m', ' p') FROM dual;

SELECT nume, data_ang, Add_months(data_ang, 3) data_mod FROM angajati
WHERE id_dep = 10;

SELECT nume, data_ang, Last_day(data_ang) ultima_zi FROM angajati
WHERE id_dep = 10;

SELECT Next_day('24-mar-2014', 'Monday') urmatoarea_luni FROM dual;

SELECT nume, data_ang,
       Months_between('01-jan-2014', data_ang) luni_vechime1,
       Months_between(data_ang, '01-jan-2014') luni_vechime2
FROM angajati WHERE id_dep = 10;

SELECT data_ang, Round(data_ang, 'Year') rot_an FROM angajati
WHERE id_ang = 7369;

SELECT data_ang, Round(data_ang, 'Month') rot_an FROM angajati
WHERE id_ang = 7369;

SELECT data_ang, Trunc(data_ang, 'Year') rot_an FROM angajati
WHERE id_ang = 7369;

SELECT data_ang, Trunc(data_ang, 'Month') rot_an FROM angajati
WHERE id_ang = 7369;

SELECT SysDate FROM dual;

SELECT Extract(Day from SysDate) FROM dual;
SELECT Extract(Month from SysDate) FROM dual;
SELECT Extract(Year from SysDate) FROM dual;

SELECT data_ang, data_ang + 7, data_ang - 7, SysDate - data_ang FROM angajati
WHERE data_ang Like '%JUN%';

ALTER session SET NLS_Date_Format = 'DD-MM-YYYY';
SELECT SysDate from dual;

ALTER session SET NLS_Date_Format = 'DD-MM-YYYY HH24:MI:SS';
SELECT SysDate from dual;

ALTER session SET NLS_Date_Format = 'DD-Month-YYYY';
SELECT Replace(SysDate, ' ', '') from dual;

SELECT UPPER(a1.nume) NUME, Replace(a1.data_ang, ' ', '') Data_ang, LOWER(d.den_dep) denumire_dep, Substr(a2.nume, 1, 1) Initiala_sef
FROM angajati a1, angajati a2, departamente d
WHERE Length(a1.nume) = 4 AND a1.id_dep = d.id_dep AND a1.id_sef = a2.id_ang;