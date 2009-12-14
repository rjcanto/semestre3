USE AP1;
set dateformat dmy;

/*1.1 Quais as categorias com salário base superior a 1000 euros?*/

SELECT *
FROM dbo.CATEGORIA
WHERE salarioBase>1000;

/*1.2 Quais os nomes dos empregados admitidos a 10 de Maio de 2006?*/

SELECT DISTINCT nomeEmp
FROM dbo.EMPREGADO
WHERE dataAdmissao = '10-05-2006';

/*1.3 Quais os empregados que ganham menos de 1000 euros?*/

SELECT E.codEmp, E.nomeEmp
FROM dbo.EMPREGADO AS E INNER JOIN dbo.CATEGORIA AS C
		ON(E.codCat=C.codCat)
WHERE C.salarioBASE<1000;

/*1.4 Quais os projectos (código e descrição) onde participam empregados das categorias 1 e 2?*/

SELECT P.codProj, P.descProj
FROM dbo.PROJECTO AS P INNER JOIN
	( SELECT DISTINCT PAR.codProj 
	  FROM(
		 SELECT *
		 FROM dbo.EMPREGADO AS E
		 WHERE (E.codCat=1 OR E.codCat=2)) AS CAT1_2 INNER JOIN PARTICIPA AS PAR
			ON(CAT1_2.codEmp=PAR.codEmp)) AS AUX
	ON(P.codProj=AUX.codProj);


/*1.5 Quantos empregados existem em cada categoria?*/

SELECT C.codCat, COUNT(E.codEmp)
FROM dbo.EMPREGADO AS E INNER JOIN dbo.CATEGORIA AS C
	ON(E.codCat = C.codCat)
GROUP BY C.codCat
