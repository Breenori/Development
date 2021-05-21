DROP TABLE LOGBOOKENTRY;
DROP TABLE EMPLOYEE;

CREATE TABLE EMPLOYEE (
                          id INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY,
                          FIRSTNAME VARCHAR(50),
                          LASTNAME VARCHAR(50),
                          DATEOFBIRTH TIMESTAMP,
                          CONSTRAINT primary_key PRIMARY KEY (id)
);

CREATE TABLE LOGBOOKENTRY (
                              id INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY,
                              ACTIVITY VARCHAR(100),
                              STARTTIME TIMESTAMP,
                              ENDTIME TIMESTAMP,
                              EMPLOYEE_FK INTEGER,
                              CONSTRAINT EMPLOYEE_ID_FK FOREIGN KEY (EMPLOYEE_FK) REFERENCES EMPLOYEE(ID)
);