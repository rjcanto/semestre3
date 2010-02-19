/*
*	Sistemas de Informação I
*	2009/2010 Semestre Inverno
*	Trabalho Prático (Parte II)
*	
*	Elaborado por:
*	Grupo 1
*	30896 – Ricardo Canto
*	31401 – Nuno Cancelo
*	33595 – Nuno Sousa
*/

use Zhongyixue
/**
*	i)Quais os pacientes que ainda não efectuaram nenhuma consulta. 
*	nota: apresentar informação sobre BI, nome e data de registo no centro.
*/
SELECT PESSOA.BI,PESSOA.nomePessoa,PACIENTE.dataRegisto
FROM
	PESSOA INNER JOIN PACIENTE ON (PESSOA.BI = PACIENTE.BI)
WHERE PACIENTE.BI NOT IN (
	SELECT DISTINCT CONSULTA.BIPaciente 
	FROM CONSULTA
);

/**
*	ii) Quais os tratamentos e respectivos terapeutas habilitados (BI e nome), 
*	para cada um dos padrões clínicos já diagnosticados a algum paciente, desde 
*	1 de Dezembro de 2009. nota: apresentar também a informação sobre o respectivo padrão clínico.
*/

SELECT DISTINCT TERAPEUTA.BI, PESSOA.nomePessoa as Terapeuta,TRATAMENTO.descTratamento as Tratamento,
	PADRAO.nomePadrao as Padrão,PADRAO.descPadrao
FROM
	PESSOA INNER JOIN TERAPEUTA ON (PESSOA.BI = TERAPEUTA.BI)
	INNER JOIN TERAPEUTA_ESPECIALIZACAO ON (TERAPEUTA.BI = TERAPEUTA_ESPECIALIZACAO.BITerapeuta)
	INNER JOIN TRATAMENTO ON (TERAPEUTA_ESPECIALIZACAO.nomeEspecializacao=TRATAMENTO.nomeEspecializacao)
	INNER JOIN TRATAMENTO_PADRAO ON (TRATAMENTO.numTratamento = TRATAMENTO_PADRAO.numTratamento)
	INNER JOIN SINTOMA_PADRAO ON (SINTOMA_PADRAO.numPadrao = TRATAMENTO_PADRAO.numPadrao)
	INNER JOIN SINTOMA_PACIENTE ON (SINTOMA_PADRAO.numPadrao = SINTOMA_PACIENTE.numSintoma)
	INNER JOIN PADRAO ON (SINTOMA_PADRAO.numPadrao = PADRAO.numPadrao)
;
/**
*	iii) Quais os terapeutas, em funções, que ainda não realizaram nenhuma consulta 
*	mas estão habilitados a realizar algum dos tratamentos recomendados para o padrão 
*	clínico “Vazio de Sangue”. nota: mostrar a informação sobre o BI, nome e telefone dos terapeutas.
*/
SELECT TERAPEUTA.BI, PESSOA.nomePessoa as Terapeuta, PESSOA.telefone as Telefone
FROM
	PESSOA INNER JOIN TERAPEUTA ON (PESSOA.BI = TERAPEUTA.BI)
	INNER JOIN TERAPEUTA_ESPECIALIZACAO ON (TERAPEUTA.BI = TERAPEUTA_ESPECIALIZACAO.BITerapeuta)
	INNER JOIN TRATAMENTO ON (TERAPEUTA_ESPECIALIZACAO.nomeEspecializacao=TRATAMENTO.nomeEspecializacao)
	INNER JOIN TRATAMENTO_PADRAO ON (TRATAMENTO.numTratamento = TRATAMENTO_PADRAO.numTratamento)
	INNER JOIN PADRAO ON (TRATAMENTO_PADRAO.numPadrao = PADRAO.numPadrao)
WHERE PADRAO.nomePadrao = 'Vazio de Sangue' AND TERAPEUTA.BI NOT IN (
	SELECT DISTINCT CONSULTA.BITerapeuta
	FROM CONSULTA
);

/**
*	iv) Qual o padrão clínico mais frequentemente diagnosticado aos pacientes cujo 
*	estado civil é “casado”. nota: mostrar a informação sobre a referência, a descrição e a designação.
*/
SELECT TOP 1 COUNT(PADRAO.numPadrao)as Frequência, PADRAO.numPadrao as Referência, PADRAO.nomePadrao as Designação, PADRAO.descPadrao
FROM 
	PADRAO INNER JOIN SINTOMA_PADRAO ON (PADRAO.numPadrao = SINTOMA_PADRAO.numPadrao)
	INNER JOIN SINTOMA_PACIENTE ON (SINTOMA_PADRAO.numSintoma = SINTOMA_PACIENTE.numSintoma)
	INNER JOIN PACIENTE ON (SINTOMA_PACIENTE.BIPaciente = PACIENTE.BI)
WHERE PACIENTE.estadoCivil = 'Casado'
GROUP BY PADRAO.numPadrao, PADRAO.nomePadrao, PADRAO.descPadrao
ORDER BY 1 DESC;

/**
*	v) Quais os terapeutas, que também são pacientes, e que já realizaram algum tratamento 
*	para o qual estão também habilitados. nota: mostrar a informação sobre o BI, nome, data de nascimento, email.
*/
SELECT TERAPEUTA.BI as Identificação, PESSOA.nomePessoa as Nome, PESSOA.dataNasc as 'Data de Nascimento', PACIENTE.email as 'Email'
FROM 
	TERAPEUTA INNER JOIN PESSOA ON (TERAPEUTA.BI = PESSOA.BI)
	INNER JOIN PACIENTE ON (TERAPEUTA.BI = PACIENTE.BI)
	INNER JOIN SESSAO ON (PACIENTE.BI = SESSAO.BIPaciente)
	INNER JOIN TRATAMENTO ON (SESSAO.numTratamento = TRATAMENTO.numTratamento)
	INNER JOIN ESPECIALIZACAO ON (ESPECIALIZACAO.nomeEspecializacao = TRATAMENTO.nomeEspecializacao)
WHERE (ESPECIALIZACAO.nomeEspecializacao = TRATAMENTO.nomeEspecializacao)
UNION
SELECT TERAPEUTA.BI as Identificação, PESSOA.nomePessoa as Nome, PESSOA.dataNasc as 'Data de Nascimento', PACIENTE.email as 'Email'
FROM 
	TERAPEUTA INNER JOIN PESSOA ON (TERAPEUTA.BI = PESSOA.BI)
	INNER JOIN PACIENTE ON (TERAPEUTA.BI = PACIENTE.BI)
	INNER JOIN CONSULTA_NAOPRESENCIAL ON (PACIENTE.BI = CONSULTA_NAOPRESENCIAL .BIPaciente)
	INNER JOIN TRATAMENTO ON (CONSULTA_NAOPRESENCIAL.numTratamento = TRATAMENTO.numTratamento)
	INNER JOIN ESPECIALIZACAO ON (ESPECIALIZACAO.nomeEspecializacao = TRATAMENTO.nomeEspecializacao)
WHERE (ESPECIALIZACAO.nomeEspecializacao = TRATAMENTO.nomeEspecializacao)

/**
*	vi) Qual(is) o(s) paciente(s) que não frequenta(m) a clínica há mais tempo. 
*	nota: contemplar toda a informação disponível sobre o paciente.
*/
SELECT CONSULTA.dataConsulta  as 'Última Consulta', PESSOA.nomePessoa as Nome,PESSOA.BI, PESSOA.NIF, PESSOA.idade, 
	PESSOA.dataNasc as 'Data Nascimento',PESSOA.morada, PESSOA.telefone, PACIENTE.dataRegisto as 'Data Registo', 
	PACIENTE.declRespon as Declaração, PACIENTE.email, PACIENTE.estadoCivil as 'Estado Civil', PACIENTE.profissao as Profissão
FROM PESSOA INNER JOIN PACIENTE ON (PESSOA.BI = PACIENTE.BI)
	INNER JOIN CONSULTA ON (PACIENTE.BI = CONSULTA.BIPaciente)
WHERE CONSULTA.dataConsulta IN
	(SELECT TOP 1 MAX(CONSULTA.dataConsulta)
	FROM 
		CONSULTA INNER JOIN PACIENTE ON (CONSULTA.BIPaciente = PACIENTE.BI)
	GROUP BY PACIENTE.BI
	)

/**
*	vii) Para cada um dos tratamentos presenciais, qual o somatório total de horas de 
*	terapia já realizadas no centro. nota: ordenar por ordem decrescente do total de horas.
*/
SELECT SUM(DATEDIFF(MINUTE, '0:00:00', SESSAO.duracao))/60.0 as 'Total Horas', SESSAO.numTratamento as Tratamento
FROM
	SESSAO
GROUP BY SESSAO.numTratamento
ORDER BY 1 DESC
;
/**
*	viii) Quais os terapeutas que estão habilitados a realizar todos os tratamentos 
*	disponíveis no centro. nota: ordenar os terapeutas por ordem decrescente de idade.
*/
SELECT PESSOA.nomePessoa as Terapeuta, PESSOA.idade as Idade
FROM PESSOA INNER JOIN TERAPEUTA ON (PESSOA.BI = TERAPEUTA.BI)
WHERE TERAPEUTA.emFuncoes = 1 AND NOT EXISTS (
	SELECT ESPECIALIZACAO.nomeEspecializacao
	FROM ESPECIALIZACAO 
	WHERE nomeEspecializacao NOT IN (
		SELECT TERAPEUTA_ESPECIALIZACAO.nomeEspecializacao FROM TERAPEUTA_ESPECIALIZACAO
		WHERE (TERAPEUTA.BI  = TERAPEUTA_ESPECIALIZACAO.BITerapeuta)
))
ORDER BY PESSOA.idade DESC
;

/**
*	ix) Quais os pacientes a quem já foi receitada mais do que 3 vezes a fórmula de 
*	fitoterapia nº 33. nota: mostrar toda a informação relativa ao paciente.
*/
SELECT PACIENTE.*, PESSOA.*
FROM PESSOA INNER JOIN PACIENTE ON (PESSOA.BI = PACIENTE.BI)
	INNER JOIN CONSULTA_NAOPRESENCIAL ON (PACIENTE.BI = CONSULTA_NAOPRESENCIAL.BIPaciente)
	INNER JOIN NAOPRESENCIAL ON (CONSULTA_NAOPRESENCIAL.numTratamento = NAOPRESENCIAL.numTratamento)
WHERE (NAOPRESENCIAL.numFormula = 33)
GROUP BY PACIENTE.BI,PESSOA.nomePessoa, PESSOA.NIF,PACIENTE.profissao,PACIENTE.estadoCivil,PESSOA.dataNasc,
	PACIENTE.declRespon,PACIENTE.email,PACIENTE.dataRegisto,PESSOA.idade,PESSOA.telefone,PESSOA.BI,PESSOA.morada
HAVING (COUNT(PACIENTE.BI) > 3);	

/**
*	x) Quais os pacientes que estejam inscritos na clinica e que tenham desempenhado
*	funções como terapeutas.
*/
SELECT PESSOA.nomePessoa,TERAPEUTA.emFuncoes 
FROM 
	TERAPEUTA INNER JOIN PESSOA ON (TERAPEUTA.BI = PESSOA.BI)	
WHERE TERAPEUTA.emFuncoes = 0 AND EXISTS (
	SELECT PACIENTE.BI FROM PACIENTE
	WHERE PACIENTE.BI = TERAPEUTA.BI
);