/*USE Zhongyixue

BEGIN TRANSACTION createViews
*/

/*a) Listar todos os pacientes do centro, contemplando 
a informação respeitante apenas aos dados pessoais;*/
CREATE VIEW LISTA_PACIENTES
	(Nome, BI, NIF, Morada, Telefone, Idade, 
	"Data Nascimento", Profissao, "Estado Civil", "Decl. Responsabilidade", 
	Email, "Data Registo")
	AS SELECT PESSOA.nomePessoa,PESSOA.BI, PESSOA.NIF,
		PESSOA.morada, PESSOA.telefone, PESSOA.idade
		,PESSOA.dataNasc, PACIENTE.profissao, 
		PACIENTE.estadoCivil,PACIENTE.declRespon,PACIENTE.email,
		PACIENTE.dataRegisto
	FROM PESSOA INNER JOIN PACIENTE ON (PESSOA.BI = PACIENTE.BI)
	
/*b) Apresentar a ficha de diagnóstico diferencial para um determinado paciente;*/
CREATE VIEW DIAGNOSTICO_PACIENTES
	("Nome Paciente", "BI Paciente", "NIF Paciente", Morada, Telefone, Idade, 
	"Data Nascimento", Profissao, "Estado Civil", "Decl. Responsabilidade",
	Email, "Data Registo", "Nome Sintoma", "Desc. Sintoma", "Data Sintoma", 
	Notas, "Nome Padrao", "Desc. Padrao", "Nome Terapeuta" )
	AS SELECT P.nomePessoa,P.BI, P.NIF,
		P.morada, P.telefone, P.idade
		,P.dataNasc, PACIENTE.profissao, 
		PACIENTE.estadoCivil,PACIENTE.declRespon,PACIENTE.email,
		PACIENTE.dataRegisto, SINTOMA.nomeSintoma, SINTOMA.descSintoma,
		SINTOMA_PACIENTE.dataSintoma, SINTOMA_PACIENTE.notas, 
		PADRAO.nomePadrao, PADRAO.descPadrao, T.nomePessoa
	FROM PESSOA as P INNER JOIN PACIENTE ON (P.BI = PACIENTE.BI)
	INNER JOIN SINTOMA_PACIENTE ON (PACIENTE.BI = SINTOMA_PACIENTE.BIPaciente)
	INNER JOIN SINTOMA ON (SINTOMA.numSintoma = SINTOMA_PACIENTE.numSintoma)
	INNER JOIN PACIENTE_SINTOMA_TERAPEUTA ON (PACIENTE_SINTOMA_TERAPEUTA.BIPaciente = PACIENTE.BI)
	INNER JOIN PADRAO ON (PADRAO.numPadrao = PACIENTE_SINTOMA_TERAPEUTA.numPadrao)
	INNER JOIN TERAPEUTA ON (TERAPEUTA.BI = PACIENTE_SINTOMA_TERAPEUTA.BITerapeuta)
	INNER JOIN PESSOA as T ON (T.BI = TERAPEUTA.BI )

CREATE VIEW LISTA_CONSULTAS
	("BI Paciente", "Nome Paciente", "BI Terapeuta", "Nome Terapeuta", 
	"Num Consulta", "Data Consulta", "Relatorio")
	AS SELECT P.BI, P.nomePessoa, T.BI, T.nomePessoa, 
		CONSULTA.numConsulta, CONSULTA.dataConsulta, CONSULTA.relatorio
	FROM PESSOA as P INNER JOIN PACIENTE ON (P.BI = PACIENTE.BI)
	INNER JOIN CONSULTA ON (P.BI = CONSULTA.BIPaciente)
	INNER JOIN PESSOA as T ON (T.BI = CONSULTA.BITerapeuta)
	INNER JOIN TERAPEUTA ON (T.BI = TERAPEUTA.BI)
	
/*c) Adicionar um Paciente;*/
/*d) Adicionar um Terapeuta;*/
/*e) Registar uma terapia de uma sessão, numa determinada consulta, indicando o terapeuta que a realiza;*/
/*f) Registar uma nova consulta para um paciente;*/
/*g) Remover a habilitação de um terapeuta para a realização de um determinado tratamento;*/
/*h) Registar a suspensão de funções de um terapeuta.*/

CREATE VIEW LISTA_TERAPEUTAS
	(Nome, BI, NIF, Morada, Telefone, Idade, 
	"Data Nascimento", "Data Conclusao", "Em Funcoes")
	AS SELECT PESSOA.nomePessoa,PESSOA.BI, PESSOA.NIF,
		PESSOA.morada, PESSOA.telefone, PESSOA.idade
		,PESSOA.dataNasc, TERAPEUTA.dataConclusao,
		TERAPEUTA.emFuncoes
	FROM PESSOA INNER JOIN TERAPEUTA ON (PESSOA.BI = TERAPEUTA.BI)
	