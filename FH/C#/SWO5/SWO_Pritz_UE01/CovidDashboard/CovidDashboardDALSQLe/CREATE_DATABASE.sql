CREATE DATABASE Covid;

DROP TABLE report;
DROP TABLE district;
DROP TABLE [user];
DROP TABLE [state];


CREATE TABLE [state] (
	id BIGINT NOT NULL PRIMARY KEY,
	[name] NVARCHAR(50) NOT NULL
);

CREATE TABLE district (
	id BIGINT NOT NULL PRIMARY KEY,
	[name] NVARCHAR(50) NOT NULL,
	[population] BIGINT NOT NULL,
	state_id BIGINT NOT NULL,
	CONSTRAINT FK_DistrictState FOREIGN KEY (state_id) REFERENCES [state](id),
);

CREATE TABLE [user] (
	id BIGINT NOT NULL IDENTITY(0,1) PRIMARY KEY,
	[name] NVARCHAR(50) NOT NULL,
	[password] NVARCHAR(64) NOT NULL,
	CONSTRAINT nameUnique UNIQUE([name])
);

CREATE TABLE report (
	id BIGINT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	report_date DATETIME NOT NULL,
	num_infected BIGINT NOT NULL,
	num_recovered BIGINT NOT NULL,
	num_deceased BIGINT NOT NULL,
	incidence FLOAT NOT NULL,
	district_id BIGINT NOT NULL,
	[user_id] BIGINT NOT NULL,
	CONSTRAINT FK_ReportDistrict FOREIGN KEY (district_id) REFERENCES district(id),
	CONSTRAINT FK_ReportUser FOREIGN KEY ([user_id]) REFERENCES [user](id)
);

INSERT INTO [state](id, [name]) VALUES(1,'Burgenland');
INSERT INTO [state](id, [name]) VALUES(2,'Kärnten');
INSERT INTO [state](id, [name]) VALUES(3,'Niederösterreich');
INSERT INTO [state](id, [name]) VALUES(4,'Oberösterreich');
INSERT INTO [state](id, [name]) VALUES(5,'Salzburg');
INSERT INTO [state](id, [name]) VALUES(6,'Steiermark');
INSERT INTO [state](id, [name]) VALUES(7,'Tirol');
INSERT INTO [state](id, [name]) VALUES(8,'Vorarlberg');
INSERT INTO [state](id, [name]) VALUES(9,'Wien');

