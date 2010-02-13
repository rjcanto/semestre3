/*------------------------------------------------------------------------------
ISEL - INSTITUTO SUPERIOR DE ENGENHARIA DE LISBOA
LEIC - LICENCIATURA DE ENGENHARIA DE INFORMÁTICA E DE COMPUTADORES
ANO LECTIVO 2009-2010
SEMESTRE DE INVERNO
GRUPO 1:
30896 - RICARDO CANTO
31401 - NUNO CANCELO
33595 - NUNO SOUSA

RESOLUÇÃO DA FICHA DE "AULA PRÁTICA SOBRE SQL"
------------------------------------------------------------------------------*/
USE SI1;

IF DB_ID('AP1') IS NOT NULL
	DROP DATABASE AP1;

	
CREATE DATABASE AP1;
GO

USE AP1;
SET DATEFORMAT DMY;
			
CREATE TABLE DBO.CATEGORIA(
		CODCAT INT CONSTRAINT PK_CATEGORIA PRIMARY KEY,
		DESIGNACAO VARCHAR(50) NOT NULL,
		SALARIOBASE MONEY NOT NULL CONSTRAINT CK1_SALARIO CHECK(SALARIOBASE>0)

		);
GO
CREATE TABLE DBO.EMPREGADO(
		CODEMP INT CONSTRAINT PK_EMPREGADO PRIMARY KEY, 
		BI CHAR(10) CONSTRAINT AK_EMPREGADO UNIQUE, 
		NOMEEMP VARCHAR(50) NOT NULL, 
		DATAADMISSAO DATE NOT NULL, 
		GENERO CHAR(1) NOT NULL, 
		CODCAT INT NOT NULL CONSTRAINT FK1_EMPREGADO FOREIGN KEY(CODCAT) REFERENCES CATEGORIA(CODCAT),
		CODEMPCHEFE INT CONSTRAINT FK2_EMPREGADO FOREIGN KEY(CODEMPCHEFE) REFERENCES EMPREGADO(CODEMP),
		CONSTRAINT CK1_EMPREGADO CHECK(GENERO='M' OR GENERO='F')
		);
GO
CREATE TABLE DBO.PROJECTO(
		CODPROJ INT CONSTRAINT PK_PROJECTO PRIMARY KEY, 
		DESCPROJ VARCHAR(50) NOT NULL, 
		NUMHORAS INT NOT NULL
		);
GO
CREATE TABLE DBO.PARTICIPA(
		CODEMP INT CONSTRAINT FK1_PARTICIPA FOREIGN KEY(CODEMP) REFERENCES EMPREGADO(CODEMP),
		CODPROJ INT CONSTRAINT FK2_PARTICIPA FOREIGN KEY(CODPROJ) REFERENCES PROJECTO(CODPROJ)
		CONSTRAINT PK_PARTICIPA PRIMARY KEY (CODEMP,CODPROJ) 
		);
GO