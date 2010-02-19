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

use Zhongyixue ;
set nocount on;
set xact_abort on;
set dateformat dmy;
go

begin transaction populateTables

raiserror('Starting...',0,1) --info
/*
*	dbo.SINTOMA
*/

insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(1,'Febre','Descrição do sintoma Febre');
insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(2,'Dor Abdominal','Descrição do sintoma Dor Abdominal');
insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(3,'Dor de cabeça','Descrição do sintoma Dor de Cabeça' );
insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(4,'Desmaio','Descrição do sintoma Desmaio' );
insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(5,'Perda de Apetite','Descrição do sintoma Perda de Apetite' );
insert into dbo.SINTOMA( numSintoma, nomeSintoma, descSintoma ) values(6,'Astenia','Descrição do sintoma Astenia' );

/*
*	dbo.PADRAO
*/
insert into dbo.PADRAO( numPadrao, nomePadrao, descPadrao ) values  (1,'Estase de Sangue','Padrao Clinico Estase de Sangue')
insert into dbo.PADRAO( numPadrao, nomePadrao, descPadrao ) values  (2,'Calor no Sangue ','Padrao Clinico Calor no Sangue ')
insert into dbo.PADRAO( numPadrao, nomePadrao, descPadrao ) values  (3,'Qi rebelde','Padrao Clinico Qi rebelde')
insert into dbo.PADRAO( numPadrao, nomePadrao, descPadrao ) values  (4,'Vazio de Sangue','Padrao Clinico Vazio de Sangue')
insert into dbo.PADRAO( numPadrao, nomePadrao, descPadrao ) values  (5,'Afundamento do Qi','Padrao Clinico Afundamento do Qi')


/*
*	dbo.SINTOMA_PADRAO
*/
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (1,1);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (1,3);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (2,1);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (3,2);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (4,4);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (4,6);
insert into dbo.SINTOMA_PADRAO( numPadrao, numSintoma ) values (5,2);
 
/*
*	dbo.PESSOA
*/
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('12345678-9','12345678','José Gomercindo','Rua B, Lote 23','+351 219983879',134,'05-10-1876') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('13345679-9','13345778','Aníbel Fonseca','Rua F, Lote 4','+44 20083879',45,'06-11-1965') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('14345680-9','14345878','Cátia Vanessa','Rua J, Lote 67','+351 201238579',27,'11-05-1982') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('15345681-9','15345978','Urubina João','Rua B, Lote 23','+351 219543879',56,'10-10-1954') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('16345682-9','16346078','Boaventura Francisco','Rua F, Lote 54','+351 219984879',34,'06-07-1975') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('16345700-9','16346700','Joaquina Felisberta','Rua A, Lote 3','+351 210084879',34,'06-06-1975') ;
insert into dbo.PESSOA(BI,NIF,nomePessoa,morada,telefone,idade,dataNasc) values ('34343434-3','34343434','Miguel Micael','Rua K, Nº98','+351 098987786',87,'05-05-1922') ;
/*
*	dbo.PACIENTE
*/

insert into dbo.PACIENTE(BI,profissao,estadoCivil,declRespon,email,dataRegisto) values ('12345678-9','Sapateiro','Casado',null,'gomercindo@si1.pt','01-01-2001');
insert into dbo.PACIENTE(BI,profissao,estadoCivil,declRespon,email,dataRegisto) values ('13345679-9','Estudante','Separado',null,null,'01-01-2009');
insert into dbo.PACIENTE(BI,profissao,estadoCivil,declRespon,email,dataRegisto) values ('14345680-9','Astronauta','Casado',null,null,'01-01-2010');
insert into dbo.PACIENTE(BI,profissao,estadoCivil,declRespon,email,dataRegisto) values ('34343434-3','Saltibancos','Viúvo',null,'1@2.pt','05-07-2009');

/*
*	dbo.SINTOMA_PACIENTE
*/
insert into dbo.SINTOMA_PACIENTE(numSintoma,BIPaciente,dataSintoma,notas) values (4,'12345678-9','01-01-2010','xpto');
insert into dbo.SINTOMA_PACIENTE(numSintoma,BIPaciente,dataSintoma,notas) values (6,'14345680-9','12-12-2009','abcd');
insert into dbo.SINTOMA_PACIENTE(numSintoma,BIPaciente,dataSintoma,notas) values (3,'13345679-9','08-08-2009','qwer');

/*
*	dbo.TERAPEUTA
*/
insert into dbo.TERAPEUTA(BI,dataConclusao,emFuncoes) values ('15345681-9','01-12-1972',1);
insert into dbo.TERAPEUTA(BI,dataConclusao,emFuncoes) values ('16345682-9','01-10-1985',1);
insert into dbo.TERAPEUTA(BI,dataConclusao,emFuncoes) values ('16345700-9','01-10-1945',1);
insert into dbo.TERAPEUTA(BI,dataConclusao,emFuncoes) values ('34343434-3','11-05-1982',0);

/**
*	dbo.PACIENTE_SINTOMA_TERAPEUTA
*/
insert into dbo.PACIENTE_SINTOMA_TERAPEUTA(BIPaciente,numPadrao,BITerapeuta) values ('12345678-9',1,'15345681-9');
insert into dbo.PACIENTE_SINTOMA_TERAPEUTA(BIPaciente,numPadrao,BITerapeuta) values ('14345680-9',3,'15345681-9');

/**
*	dbo.ESPECIALIZACAO
*/
insert into dbo.ESPECIALIZACAO(nomeEspecializacao) values ('A');
insert into dbo.ESPECIALIZACAO(nomeEspecializacao) values ('B');
insert into dbo.ESPECIALIZACAO(nomeEspecializacao) values ('C');

/**
*	dbo.TERAPEUTA_ESPECIALIZACAO
*/
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('15345681-9','A');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('16345682-9','B');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('16345700-9','B');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('16345700-9','A');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('16345700-9','C');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('34343434-3','C');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('34343434-3','B');
insert into dbo.TERAPEUTA_ESPECIALIZACAO(BITerapeuta, nomeEspecializacao) values ('34343434-3','A');

/**
*	dbo.TRATAMENTO
*/
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (1,'Tratamento 1','Presencial','B');
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (2,'Tratamento 2','Presencial','B');
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (3,'Tratamento 3','Não Presencial','A');
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (4,'Tratamento 4','Presencial','A');
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (5,'Tratamento 5','Não Presencial','B');
insert into dbo.TRATAMENTO(numTratamento,descTratamento,tipoTramento,nomeEspecializacao) values (6,'Tratamento 6','Não Presencial','C');

/**
*	dbo.PRESENCIAL
*/
insert into dbo.PRESENCIAL(numTratamento,tipoTratamento) values (1,'Moxabustão');
insert into dbo.PRESENCIAL(numTratamento,tipoTratamento) values (2,'Acupunctura');
insert into dbo.PRESENCIAL(numTratamento,tipoTratamento) values (4,'Massagem');

/**
*	dbo.NAOPRESENCIAL
*/
insert into dbo.NAOPRESENCIAL(numTratamento,numFormula,nomeFormula,composicao) values (3,1,'Tai Hoy Xue','dasd');
insert into dbo.NAOPRESENCIAL(numTratamento,numFormula,nomeFormula,composicao) values (5,2,'Ju Goi To','adasdasdasd');
insert into dbo.NAOPRESENCIAL(numTratamento,numFormula,nomeFormula,composicao) values (6,33,'Kio Ji Ti','adsadasdas');

/**
*	dbo.TRATAMENTO_PADRAO
*/
insert into dbo.TRATAMENTO_PADRAO(numTratamento,numPadrao) values (1,4);
insert into dbo.TRATAMENTO_PADRAO(numTratamento,numPadrao) values (2,3);
insert into dbo.TRATAMENTO_PADRAO(numTratamento,numPadrao) values (4,5);

/**
*	dbo.CONSULTA
*/
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('12345678-9','15345681-9',1,'01-11-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('12345678-9','16345682-9',2,'01-05-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('14345680-9','34343434-3',3,'23-02-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('14345680-9','34343434-3',4,'30-06-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('14345680-9','34343434-3',5,'20-10-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('14345680-9','34343434-3',6,'18-01-2010','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('14345680-9','34343434-3',7,'04-01-2009','');
insert into dbo.CONSULTA(BIPaciente, BITerapeuta, numConsulta, dataConsulta, relatorio) values ('34343434-3','16345700-9',8,'04-11-2009','');

/**
* dbo.CONSULTA_NAOPRESENCIAL
*/
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('12345678-9',2,3,400,2,'almoço e jantar') ;
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('12345678-9',2,6,500,2,'almoço e jantar') ;
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('14345680-9',4,6,400,2,'almoço e jantar') ;
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('14345680-9',5,6,200,2,'almoço e jantar') ;
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('14345680-9',6,6,100,2,'almoço e jantar') ;
insert into dbo.CONSULTA_NAOPRESENCIAL(BIPaciente,numConsulta,numTratamento,quantidade,vezesDia,ocasioes) values ('14345680-9',7,6,100,2,'almoço e jantar') ;

/**
* dbo.SESSAO
*/
insert into dbo.SESSAO(numSessao,numTratamento,numConsulta,BIPaciente,BITerapeuta,duracao,descSessao) values (1,1,2,'12345678-9','16345682-9','01:30','asçldjalksfjal') ;
insert into dbo.SESSAO(numSessao,numTratamento,numConsulta,BIPaciente,BITerapeuta,duracao,descSessao) values (2,2,3,'14345680-9','34343434-3','02:30','Adsasdl') ;
insert into dbo.SESSAO(numSessao,numTratamento,numConsulta,BIPaciente,BITerapeuta,duracao,descSessao) values (3,2,8,'34343434-3','16345700-9','00:30','Adsasdl') ;



raiserror('... OK',0,1) --info
commit