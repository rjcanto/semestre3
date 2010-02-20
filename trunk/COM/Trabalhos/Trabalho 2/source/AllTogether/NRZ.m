%
%NRZ(bits,Amp,CarrierFreq)
%bits - Sinal Binário de Entrada
%Amp - Amplitude do sinal desejado (0 -> Amp)
%CarrierFreq - Frequencia da Portadora.
%
%Retorno:
%FS - Frequencia de Amostragem, Respeitando o Ritmo de Nyquist
%myX - Sinal de retorno codificado com o NRZ.
function [myX,mynX,FS]=NRZ(signal,Amp,TB,CarrierFreq)
	if(nargin == 0)
		fprintf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		fprintf('Têm argumentos a mais.\n');
		return;
	elseif (nargin == 2)
		fprintf('Assumindo a Amplitude 5 e frequencia da portadora de 100Hz.\n');	
		CarrierFreq=100;
		Amp=5;
	elseif (nargin == 3)
		fprintf('Assumindo a frequencia da portadora de 100Hz.\n');	
		CarrierFreq=100;
	end
		

	%Tempo de Bit do Nosso NRZ
	%nrzTs=TB;

    %Numero de elementos do sinal de entrada
	nbrBits=length(signal);	
	
    %Frequencia Fundamental de Saída, respeitando o Ritmo de Nyquist
    %FS=2.2*(1/(TB));
    FS=44000;
    
    %tamanho do array de tempos da nossa base tempo por bit
	t=length(0:1/(FS-1):TB);

    myX=[];
    mynX=[];

    %Ciclo que vai criar a onda quadrada
	k=1;
	for i=1:nbrBits
		if( signal(i) == 1)
				myX = [myX ones(1,t).*Amp];
				mynX = [mynX zeros(1,t)];
			else
 				myX = [myX zeros(1,t)];
 				mynX = [mynX ones(1,t).*Amp];
 		end 
    end
end