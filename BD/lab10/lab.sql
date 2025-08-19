CREATE TABLE exemplu (
    data_implicata date DEFAULT sysdate,
    numar_implicit number(7, 2) DEFAULT 7.24,
    string_implicit varchar2(5) DEFAULT 'test',
    operator varchar2(10) DEFAULT user
);

SELECT table_name, column_name, data_default FROM user_tab_columns
WHERE table_name='EXEMPLU';


CREATE TABLE studenti(
    facultate char(30) DEFAULT 'ACS',
    catedra char(20),
    cnp number(13),
    nume varchar2(30),
    data_nasterii date,
    an_univ number(4) default 2019,
    medie_admitere number(4, 2),
    discip_oblig varchar2(20) default 'Matematica',
    discip_optio varchar2(20) default 'Fizica',
    operator varchar2(20) default user,
    data_op timestamp default sysdate
);


CREATE TABLE dept_20
AS
SELECT id_dep, nume, data_ang, salariu + nvl(comision, 0) venit
FROM angajati
WHERE id_dep = 20;


CREATE TABLE dept_30 (
    id DEFAULT 30,
    nume NOT NULL,
    data_ang,
    prima
) AS
    SELECT id_dep, nume, data_ang, round(0.15*(salariu + nvl(comision, 0)), 0)
    FROM angajati WHERE id_dep = 30;


CREATE TABLE exemplu2 (
    col_1 number(2) CONSTRAINT nn_col_1 NOT NULL,
    col_2 varchar2(20) NOT NULL
);


CREATE TABLE exemplu3 (
    col_1 number(2) CONSTRAINT uq_col unique,
    col_2 varchar2(20) unique
);


CREATE TABLE exemplu4 (
    col_1 number(2),
    col_2 varchar2(20),
    CONSTRAINT uq_col_1 unique(col_1),
    unique(col_2)
);


CREATE TABLE exemplu5 (
    col_1 number(2),
    col_2 varchar2(20),
    CONSTRAINT uq_col_2 unique(col_1, col_2)
);


CREATE TABLE functii (
    cod number(2) CONSTRAINT pk_cod PRIMARY KEY,
    functie varchar2(20),
    data_vigoare DATE DEFAULT SYSDATE
);


CREATE TABLE persoane (
    nume varchar2(20),
    prenume varchar2(20),
    serie_ci varchar2(2),
    cod_ci number(6),
    cnp number(13),
    CONSTRAINT pk_persoane PRIMARY KEY(serie_ci, cod_ci, cnp)
);


ALTER TABLE departamente ADD CONSTRAINT id_unic_dep UNIQUE(id_dep);

CREATE TABLE angajati2 (
    id_ang number(4) CONSTRAINT pk_id_ang2 PRIMARY KEY,
    id_sef number(4),
    id_dep number(2) CONSTRAINT fk_id_ang2 REFERENCES departamente(id_dep),
    nume varchar2(20),
    functie varchar2(9),
    data_ang date,
    salariu number(7, 2),
    comision number(7, 2),
    CONSTRAINT fk_id_sef2 FOREIGN KEY(id_sef) REFERENCES angajati2(id_ang)
);

CREATE TABLE angajati3 (
    id_ang number(4) CONSTRAINT pk_id_ang3 PRIMARY KEY,
    nume varchar(10) CONSTRAINT ck_nume check(nume = upper(nume)),
    functie varchar2(10),
    id_sef number(4) CONSTRAINT fk_id_sef3 REFERENCES angajati3(id_ang),
    data_ang date DEFAULT SYSDATE,
    salariu number(7, 2) CONSTRAINT nn_salariu NOT NULL,
    comision number(7, 2),
    id_dep number(2) CONSTRAINT nn_id_dep3 NOT NULL,
    CONSTRAINT fk_id_dep3 FOREIGN KEY (id_dep) REFERENCES departamente(id_dep),
    CONSTRAINT ck_comision check(comision <= salariu)
);

CREATE TABLE example6 (
    colA number(2), col2 number(2), col3 number(2),
    col4 number(2), col5 number(2), col6 number(2),
    col7 number(2), col8 number(2), col9 number(2)
);

ALTER TABLE example6 RENAME TO exampleAfter;
ALTER TABLE exampleAfter rename column colA to col1;
ALTER TABLE exampleAfter MODIFY (col1 varchar2(20));
ALTER TABLE exampleAfter MODIFY (col2 varchar2(20), col3 date);
ALTER TABLE exampleAfter SET unused(col4);
ALTER TABLE exampleAfter SET unused(col5, col6);
ALTER TABLE exampleAfter DROP unused columns;
ALTER TABLE exampleAfter ADD (col4 varchar2(20), col5 varchar2(20), col6 varchar2(20));
ALTER TABLE exampleAfter DROP column col7;
ALTER TABLE exampleAfter DROP (col8, col9);
ALTER TABLE exampleAfter ADD CONSTRAINT pk_col1_alter PRIMARY KEY (col1);
ALTER TABLE exampleAfter ADD CONSTRAINT pk_col2_alter PRIMARY KEY (col1, col2);
ALTER TABLE exampleAfter ADD CONSTRAINT fk_col21 FOREIGN KEY (col2) REFERENCES exampleAfter (col1);
ALTER TABLE exampleAfter ADD CONSTRAINT fk_col21 FOREIGN KEY (col2) REFERENCES exampleAfter(col1, col2);
ALTER TABLE exampleAfter ADD CONSTRAINT uq_col3_alter unique(col3);
ALTER TABLE exampleAfter ADD CONSTRAINT uq_col45_alter unique(col4, col5);
ALTER TABLE exampleAfter DISABLE CONSTRAINT uq_col3_alter;
ALTER TABLE exampleAfter ENABLE CONSTRAINT uq_col3_alter;
ALTER TABLE exampleAfter DROP CONSTRAINT uq_col3_alter;

ALTER TABLE angajati ADD venit number(4, 3);
ALTER TABLE angajati ADD (vechime number(4), venit_anual number(6, 2));

DROP TABLE example;
TRUNCATE TABLE example1;

CREATE TABLE dept2 (
    id_dep number(2),
    dname varchar2(14)
);

INSERT INTO dept2 values (50, 'IT');
INSERT INTO dept2(id_dep) values (60);

INSERT INTO dept2
SELECT deptno, dname FROM dept WHERE deptno in (20, 30);

SELECT * FROM dept2;

UPDATE dept2
    SET dname = 'HR', id_dep = 80
    WHERE id_dep = 60;

UPDATE dept2
    SET dname = 'Human Res'
    WHERE id_dep = 80;

UPDATE dept2
    SET (id_dep, dname) = (SELECT deptno, dname FROM dept WHERE deptno = 10)
    WHERE id_dep = 20;

DELETE FROM dept2
WHERE id_dep = 80;

SELECT * FROM dept2;

DELETE FROM dept2
WHERE (id_dep, dname) IN (SELECT deptno, dname FROM dept WHERE deptno IN (10, 30));

SELECT * FROM dept2;

DELETE FROM dept2;

CREATE SEQUENCE seq_id_dep
    START WITH 1 INCREMENT BY 10
    nocache
    nocycle;

ALTER SEQUENCE seq_id_dep cycle;

INSERT INTO dept2 VALUES (seq_id_dep.nextval, 'test');

DROP SEQUENCE seq_id_dep;

CREATE OR REPLACE VIEW view_dept AS SELECT id_dep, den_dep FROM departamente;

SELECT * FROM view_dept;

INSERT INTO view_dept values(80, 'test');

SELECT * FROM view_dept;

UPDATE view_dept SET den_dep = 'HR' WHERE id_dep = 80;

SELECT * FROM view_dept;

DELETE FROM view_dept WHERE id_dep = 80;

DROP VIEW view_dept;