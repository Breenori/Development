DROP TABLE person;

CREATE TABLE person (
    id INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY,
    firstname VARCHAR(50),
    lastname VARCHAR(50),
    city VARCHAR(50),
    zip INTEGER,
    address VARCHAR(50),
    tel VARCHAR(50),
    CONSTRAINT primary_key PRIMARY KEY (id)
);
