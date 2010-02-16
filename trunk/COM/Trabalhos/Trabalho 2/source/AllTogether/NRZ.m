%
%NRZ(bits,Amp,CarrierFreq)
%bits - Sinal BinÃ¡rio de Entrada
%Amp - Amplitude do sinal desejado (0 -> Amp)
%CarrierFreq - Frequencia da Portadora.
%
%Retorno:
%FS - Frequencia de Amostragem, Respeitando o Ritmo de Nyquist
%myX - Sinal de retorno codificado com o NRZ.
function [FS,myX,mynX,n]=NRZ(signal,Amp,CarrierFreq)
	if(nargin == 0)
		fprintf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >3)
		fprintf('Têm argumentos a mais.\n');
		return;
	elseif (nargin == 1)
		fprintf('Assumindo a Amplitude 5 e frequencia da portadora de 100Hz.\n');	
		CarrierFreq=100;
		Amp=5;
	elseif (nargin == 2)
		fprintf('Assumindo a frequencia da portadora de 100Hz.\n');	
		CarrierFreq=100;
	end
		

	%Tempo de Bit do Nosso NRZ
	nrzTs=0.001;

    %Numero de elementos do sinal de entrada
	nbrBits=length(signal);	
	
    %Frequencia Fundamental de Saída, respeitando o Ritmo de Nyquist
	FS=2.2*(1/(nrzTs));
%    FS=2.2*10;
    if (FS > CarrierFreq)
        fprintf('A frequencia da portadora é inferior à frequencia de amostragem do sinal amostrado. Não vai ser possível reconstruir com exactidão o sinal.\n'); 
    end

    %Numero de elementos da nossa Base tempo.
	n=0:1/(nbrBits*FS-1):1;

    %Nosso conjunto que vai conter o sinal de saÃ­da
	myX= 1:FS;
	mynX= 1:FS;
	
    %Ciclo que vai criar a onda quadrada
	k=1;
	for i=1:nbrBits
		for  h=1:FS
			if( signal(i) == 1)
				myX(k)=Amp;
				mynX(k)=0;
				k=k+1;
			else
 				myX(k)=0;
 				mynX(k)=Amp;
 				k=k+1;
            end 
		end
    end
    %FS=FS*nbrBits;
end