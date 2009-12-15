/*
*	ISEL-DEETC-LEIC
*	2009-2010
*
*	Material didáctico para apoio 
*	à unidade curricular de 
*	Sistemas de Informação 1
*
*	Aula prática - SQL
*/

set nocount on;
set xact_abort on

go

begin transaction
raiserror('Starting...',0,1) --info
/*
*	dbo.Categoria
*/

insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(1,'A',3500);
insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(2,'B',3000);
insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(3,'C',2000);
insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(4,'D',1000);
insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(5,'E',500);
insert into dbo.CATEGORIA( codCat, designacao, salarioBase ) values(6,'E',1500);

/*
*	dbo.EMPREGADO
*/
set dateformat dmy;
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (1,'12345678-9','José Gomercindo','01-01-2001','M',1,null)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (2,'22345678-0','Aníbel Fonseca','01-02-2001','M',2,1)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (3,'32345678-2','Josefa De Óbidos','01-02-2001','F',2,1)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (4,'42345678-4','Boaventura Francisco','10-02-2002','M',3,2)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (5,'52345678-6','Boaventura Torrada','10-02-2005','M',3,2)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (6,'62345678-8','Brígida da Silva','11-02-2006','F',3,3)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (7,'72345678-0','Cátia Vanessa','11-02-2009','F',3,3)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (8,'82345678-1','Urubina João','11-02-2002','F',3,3)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (9,'92345678-3','Francisca Pinta Cruz','23-07-2003','F',3,3)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (10,'10345678-3','João Pina','10-05-2006','M',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (11,'11345678-6','Manuela Pina','25-07-2007','F',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (12,'12245678-5','José Maria Fonseca','05-06-2008','M',4,6)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (13,'13345678-1','Ana Mariana','10-05-2006','F',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (14,'14345678-4','Gertudes Paiva','28-01-2007','F',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (15,'15345678-7','Joaquina Boa Pinta','01-02-2008','F',4,6)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (16,'16345678-0','Júlio Pereira','15-03-2006','M',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (17,'17345678-2','Francisco Moita','30-04-2007','M',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (18,'18345678-5','João J. Pina','30-05-2008','M',4,7)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (19,'19345678-8','Miguel Cardoso','01-06-2008','M',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (20,'20345678-5','Nuno Silva','30-05-2008','M',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (21,'21345678-8','João J. Pereira','30-05-2008','M',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (22,'22245678-7','Maria Manuela Pina','30-05-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (23,'23345678-3','Joaquina Finto','30-05-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (24,'24345678-6','Kátia Patrícia','01-06-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (25,'25345678-9','Maia Filipe','30-05-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (26,'26345678-1','Felizberta Pinto de Sousa','30-05-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (27,'27345678-4','Josefa dos Prazeres','01-06-2008','F',5,10)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (28,'28345678-7','Francisca Francisco','30-05-2008','F',5,13)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (29,'29345678-0','Rita Faria','30-05-2008','F',5,6)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (30,'30345678-7','Cristina Linda','01-06-2008','F',5,6)
insert into dbo.EMPREGADO(codEmp, BI, nomeEmp, dataAdmissao, genero, codCat, codEmpChefe) values  (31,'31345678-0','Maria Amadora','30-05-2008','F',5,6)



/*
*	dbo.PROJECTO
*/

insert into dbo.PROJECTO(codProj, descProj, numHoras) values(1,'Projecto A',100);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(2,'Projecto B',100);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(3,'Projecto C',25);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(4,'Projecto D',50);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(5,'Projecto E',50);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(6,'Projecto F',500);
insert into dbo.PROJECTO(codProj, descProj, numHoras) values(7,'Projecto G',1000);
 
 
 /*
*	dbo.Participa
*/
insert into dbo.PARTICIPA(codEmp,codProj) values(1,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(2,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(10,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(11,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(12,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(18,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(19,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(1,2);
insert into dbo.PARTICIPA(codEmp,codProj) values(3,2);
insert into dbo.PARTICIPA(codEmp,codProj) values(13,2);
insert into dbo.PARTICIPA(codEmp,codProj) values(14,2);
insert into dbo.PARTICIPA(codEmp,codProj) values(15,2);
insert into dbo.PARTICIPA(codEmp,codProj) values(20,1);
insert into dbo.PARTICIPA(codEmp,codProj) values(2,3);
insert into dbo.PARTICIPA(codEmp,codProj) values(4,3);
insert into dbo.PARTICIPA(codEmp,codProj) values(16,3);
insert into dbo.PARTICIPA(codEmp,codProj) values(17,3);
insert into dbo.PARTICIPA(codEmp,codProj) values(3,4);
insert into dbo.PARTICIPA(codEmp,codProj) values(5,4);
insert into dbo.PARTICIPA(codEmp,codProj) values(6,4);
insert into dbo.PARTICIPA(codEmp,codProj) values(7,4);
insert into dbo.PARTICIPA(codEmp,codProj) values(3,5);
insert into dbo.PARTICIPA(codEmp,codProj) values(21,5);
insert into dbo.PARTICIPA(codEmp,codProj) values(22,5);
insert into dbo.PARTICIPA(codEmp,codProj) values(23,5);
insert into dbo.PARTICIPA(codEmp,codProj) values(24,5);
insert into dbo.PARTICIPA(codEmp,codProj) values(1,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(7,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(25,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(26,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(27,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(28,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(3,6);
insert into dbo.PARTICIPA(codEmp,codProj) values(4,7);
insert into dbo.PARTICIPA(codEmp,codProj) values(5,7);
insert into dbo.PARTICIPA(codEmp,codProj) values(29,7);
insert into dbo.PARTICIPA(codEmp,codProj) values(30,7);
insert into dbo.PARTICIPA(codEmp,codProj) values(31,7); 
insert into dbo.PARTICIPA(codEmp,codProj) values(13,7);
insert into dbo.PARTICIPA(codEmp,codProj) values(15,7); 
	
raiserror('... OK',0,1) --info
commit 