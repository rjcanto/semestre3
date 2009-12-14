/*IF EXISTS (select * from master.dbo.sysdatabases where name='AP1')*/
USE SI1;

IF db_id('AP1') is not null
	DROP DATABASE AP1;

	
CREATE DATABASE AP1;
GO

USE AP1;
set dateformat dmy;
/*
IF EXISTS(SELECT * 
		FROM INFORMATION_SCHEMA.TABLES
		WHERE TABLE_NAME = 'CATEGORIA')
DROP TABLE dbo.CATEGORIA;*/
			
CREATE TABLE dbo.CATEGORIA(
		codCat int CONSTRAINT pk_CATEGORIA PRIMARY KEY,
		designacao varchar(50) NOT NULL,
		salarioBase money NOT NULL CONSTRAINT ck1_SALARIO CHECK(salarioBase>0)

		)

CREATE TABLE dbo.EMPREGADO(
		codEmp int CONSTRAINT pk_EMPREGADO PRIMARY KEY, 
		BI char(10) CONSTRAINT ak_EMPREGADO UNIQUE, 
		nomeEmp varchar(50) NOT NULL, 
		dataAdmissao date NOT NULL, 
		genero char(1) NOT NULL, 
		codCat int NOT NULL CONSTRAINT fk1_EMPREGADO FOREIGN KEY(codCat) REFERENCES CATEGORIA(codCat),
		codEmpChefe int CONSTRAINT fk2_EMPREGADO FOREIGN KEY(codEmpChefe) REFERENCES EMPREGADO(codEmp),
		CONSTRAINT ck1_EMPREGADO CHECK(genero='M' OR genero='F')
		)

CREATE TABLE dbo.PROJECTO(
		codProj int CONSTRAINT pk_PROJECTO PRIMARY KEY, 
		descProj varchar(50) NOT NULL, 
		numHoras int NOT NULL
		)

CREATE TABLE dbo.PARTICIPA(
		codEmp int CONSTRAINT fk1_PARTICIPA FOREIGN KEY(codEmp) REFERENCES EMPREGADO(codEmp),
		codProj int CONSTRAINT fk2_PARTICIPA FOREIGN KEY(codProj) REFERENCES PROJECTO(codProj)
		)




SELECT * FROM dbo.CATEGORIA;
SELECT * FROM dbo.EMPREGADO;
SELECT * FROM dbo.PROJECTO;
SELECT * FROM dbo.PARTICIPA;
