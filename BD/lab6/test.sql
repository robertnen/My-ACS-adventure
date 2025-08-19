SELECT d.den_dep "Denumire Departament", a.nume "Nume angajat", a.data_ang "Data Angajare",
       Next_day(Add_months(Trunc(a.data_ang, 'Month'), 4), 'Monday') "Data Evaluare"
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep AND Upper(d.den_dep) = 'ACCOUNTING';


SELECT d.den_dep "Denumire Departament", a.nume "Nume angajat", a.data_ang "Data Angajare",
       Next_day(Add_months(Trunc(a.data_ang, 'Month'), 4), 'Monday') "Data Evaluare"
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep AND d.den_dep Like 'ACCOUNTING';


define data_eval = 'Next_day(Add_months(Trunc(a.data_ang, ''Month''), 4), ''Monday'')';
SELECT d.den_dep "Denumire Departament", a.nume "Nume angajat", a.data_ang "Data Angajare",
       &data_eval "Data Evaluare"
FROM angajati a, departamente d
WHERE a.id_dep = d.id_dep AND d.den_dep Like 'ACCOUNTING';


SELECT d.den_dep "Denumire Departament", a.nume "Nume angajat", a.data_ang "Data Angajare",
       Next_day(Add_months(Trunc(a.data_ang, 'Month'), 4), 'Monday') "Data Evaluare"
FROM angajati a INNER JOIN  departamente d
                        ON a.id_dep = d.id_dep
WHERE d.den_dep Like 'ACCOUNTING';


define data_eval = 'Next_day(Add_months(Trunc(a.data_ang, ''Month''), 4), ''Monday'')';
SELECT d.den_dep "Denumire Departament", a.nume "Nume angajat", a.data_ang "Data Angajare",
       &data_eval "Data Evaluare"
FROM angajati a INNER JOIN  departamente d
                        ON a.id_dep = d.id_dep
WHERE d.den_dep Like 'ACCOUNTING';