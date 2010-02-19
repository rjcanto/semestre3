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

BEGIN TRANSACTION createTables

CREATE TABLE SINTOMA(
	numSintoma int CONSTRAINT pk_SINTOMA PRIMARY KEY,
	nomeSintoma varchar(20) not null,
	descSintoma varchar(500)
) ;

CREATE TABLE PADRAO(
	numPadrao int CONSTRAINT pk_PADRAO PRIMARY KEY,
	nomePadrao varchar(20) not null,
	descPadrao varchar(500)
) ;

CREATE TABLE SINTOMA_PADRAO(
	numPadrao int,
	numSintoma int,
	CONSTRAINT pk_SINTOMA_PADRAO PRIMARY KEY ( numPadrao, numSintoma ),
	CONSTRAINT fk1_SINTOMA_PADRAO FOREIGN KEY ( numPadrao )
		REFERENCES PADRAO ( numPadrao ),
	CONSTRAINT fk2_SINTOMA_PADRAO FOREIGN KEY ( numSintoma )
		REFERENCES SINTOMA ( numSintoma )
	/*OBRIGATORIEDADES:
		Um sintoma poderá ter um ou vários padões clinicos associados;
		Um padrão clinico poderá ter um ou vários sintomas associados.
	*/
);

CREATE TABLE PESSOA(
	BI varchar(10) CONSTRAINT pk_PESSOA PRIMARY KEY,
	NIF varchar(10) CONSTRAINT ak_PESSOA UNIQUE,
	nomePessoa varchar(50) not null,
	morada varchar(30) not null,
	telefone varchar(15) not null, /*O número poderá ser internacional*/
	idade tinyint not null,
	dataNasc date not null
) ;

CREATE TABLE PACIENTE(
	BI varchar(10) not null,
	profissao varchar(20) not null,
	estadoCivil varchar(15) not null, 
		/*solteiro, divorciado, casado, união facto, viuvo, separado*/
	declRespon varbinary(max),
	email varchar(20),
	dataRegisto date not null,
	CONSTRAINT pk_PACIENTE PRIMARY KEY ( BI ),
	CONSTRAINT fk_PACIENTE FOREIGN KEY ( BI )
		REFERENCES PESSOA ( BI )
) ;

CREATE TABLE SINTOMA_PACIENTE(
	numSintoma int not null,
	BIPaciente varchar(10) not null,
	dataSintoma date not null,
	notas varchar(500),
	CONSTRAINT pk_SINTOMA_PACIENTE PRIMARY KEY (numSintoma, BIPaciente),
	CONSTRAINT fk1_SINTOMA_PACIENTE FOREIGN KEY (numSintoma)
		REFERENCES SINTOMA (numSintoma),
	CONSTRAINT fk2_SINTOMA_PACIENTE FOREIGN KEY (BIPaciente)
		REFERENCES PACIENTE (BI)
) ;
	
CREATE TABLE TERAPEUTA(
	BI varchar(10) not null,
	dataConclusao date not null,
		/*dataConclusao varchar(20) not null,*/
	emFuncoes bit not null, 
	/*1: Em funções, 0: Já não trabalha na clínica*/
	CONSTRAINT pk_TERAPEUTA PRIMARY KEY ( BI ),
	CONSTRAINT fk_TERAPEUTA FOREIGN KEY ( BI )
		REFERENCES PESSOA ( BI ),
) ;

CREATE TABLE PACIENTE_SINTOMA_TERAPEUTA(
	BIPaciente varchar(10) not null,
	numPadrao int not null,
	BITerapeuta varchar(10) not null,
	CONSTRAINT pk_PACIENTE_SINTOMA_TERAPEUTA PRIMARY KEY (BITerapeuta, numPadrao),
	CONSTRAINT fk1_PACIENTE_SINTOMA_TERAPEUTA FOREIGN KEY (BITerapeuta)
		REFERENCES TERAPEUTA (BI),
	CONSTRAINT fk2_PACIENTE_SINTOMA_TERAPEUTA FOREIGN KEY (numPadrao)
		REFERENCES PADRAO (numPadrao)
);

CREATE TABLE ESPECIALIZACAO(
	nomeEspecializacao varchar(20) CONSTRAINT pk_ESPECIALIZACAO PRIMARY KEY
);

CREATE TABLE TERAPEUTA_ESPECIALIZACAO(
	BITerapeuta varchar(10),
	nomeEspecializacao varchar(20),
	CONSTRAINT fk1_TERAPEUTA_ESPECIALIZACAO FOREIGN KEY ( BITerapeuta )
		REFERENCES TERAPEUTA ( BI ),
	CONSTRAINT fk2_TERAPEUTA_ESPECIALIZACAO FOREIGN KEY ( nomeEspecializacao ) 
		REFERENCES ESPECIALIZACAO ( nomeEspecializacao )
);
CREATE TABLE TRATAMENTO(
	numTratamento int,
	descTratamento varchar(500) not null,
	tipoTramento varchar(15) not null,
		/*"Presencial" ou "Não Presencial"*/
	nomeEspecializacao varchar(20),
	CONSTRAINT pk_TRATAMENTO PRIMARY KEY ( numTratamento ),
	CONSTRAINT fk_TRATAMENTO FOREIGN KEY ( nomeEspecializacao )
		REFERENCES ESPECIALIZACAO ( nomeEspecializacao )
);

CREATE TABLE PRESENCIAL(
	numTratamento int,
	tipoTratamento varchar(11),
	/*"Massagem", "Acupunctura" ou "Moxabustão"*/
	CONSTRAINT pk_PRESENCIAL PRIMARY KEY ( numTratamento ),
	CONSTRAINT fk_PRESENCIAL FOREIGN KEY ( numTratamento )
		REFERENCES TRATAMENTO ( numTratamento )
);

CREATE TABLE NAOPRESENCIAL(
	numTratamento int,
	numFormula int,
	nomeFormula varchar(20) not null,
	composicao varchar(100) not null,
	CONSTRAINT pk_NAOPRESENCIAL PRIMARY KEY ( numTratamento ),
	CONSTRAINT fk_NAOPRESENCIAL FOREIGN KEY ( numTratamento )
		REFERENCES TRATAMENTO ( numTratamento ),
	CONSTRAINT ak_NAOPRESENCIAL UNIQUE ( numFormula ),
);

CREATE TABLE TRATAMENTO_PADRAO(
	numTratamento int,
	numPadrao int,
	CONSTRAINT fk1_TRATAMENTO_PADRAO FOREIGN KEY ( numTratamento )
		REFERENCES TRATAMENTO ( numTratamento ),
	CONSTRAINT fk2_TRATAMENTO_PADRAO FOREIGN KEY ( numPadrao )
		REFERENCES PADRAO ( numPadrao )
);
CREATE TABLE CONSULTA(
	BIPaciente varchar(10),
	BITerapeuta varchar(10),
	numConsulta int not null,
	dataConsulta date not null,
	relatorio varchar(500),
	CONSTRAINT pk_CONSULTA PRIMARY KEY ( BIPaciente, numConsulta ),
	CONSTRAINT fk1_CONSULTA FOREIGN KEY ( BIPaciente )
		REFERENCES PACIENTE ( BI ),
	CONSTRAINT fk2_CONSULTA FOREIGN KEY ( BITerapeuta )
		REFERENCES TERAPEUTA ( BI ),			
);

CREATE TABLE CONSULTA_NAOPRESENCIAL(
	BIPaciente varchar(10),
	numConsulta int,
	numTratamento int,
	quantidade int not null,
	vezesDia tinyint not null,
	ocasioes varchar(20) not null,
	CONSTRAINT pk_CONSULTA_NAOPRESENCIAL PRIMARY KEY ( BIPaciente, numConsulta, numTratamento ),
	CONSTRAINT fk1_CONSULTA_NAOPRESENCIAL FOREIGN KEY ( BIPaciente, numConsulta )
		REFERENCES CONSULTA ( BIPaciente, numConsulta ),
	CONSTRAINT fk2_CONSULTA_NAOPRESENCIAL FOREIGN KEY ( numTratamento )
		REFERENCES NAOPRESENCIAL ( numTratamento )	
);


CREATE TABLE SESSAO(
	numSessao int,
	numTratamento int,
	numConsulta int,
	BIPaciente varchar(10),
	BITerapeuta varchar(10),
	duracao time,
	descSessao varchar(500) not null,
	CONSTRAINT pk_SESSAO PRIMARY KEY ( numSessao, numTratamento, numConsulta ),
	CONSTRAINT fk1_SESSAO FOREIGN KEY ( numTratamento )
		REFERENCES PRESENCIAL ( numTratamento ),
	CONSTRAINT fk2_SESSAO FOREIGN KEY ( BIPaciente, numConsulta )
		REFERENCES CONSULTA ( BIPaciente, numConsulta ),
	CONSTRAINT fk3_SESSAO FOREIGN KEY ( BITerapeuta )
		REFERENCES TERAPEUTA ( BI )
);

COMMIT TRANSACTION createTables ;