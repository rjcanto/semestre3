%
%NRZ(bits,Amp,CarrierFreq)
%bits - Sinal Binário de Entrada
%Amp - Amplitude do sinal desejado (0 -> Amp)
%CarrierFreq - Frequencia da Portadora.
%
%Retorno:
%FS - Frequencia de Amostragem, Respeitando o Ritmo de Nyquist
%myX - Sinal de retorno codificado com o NRZ.
%


function [FS,myX,mynX]=NRZ(bits,Amp,CarrierFreq)
	if(nargin == 0)
		printf("É necessário mais argumentos.\n");
		return;
	elseif(nargin >3)
		printf("Têm argumentos a mais.\n");
		return;
	elseif (nargin == 1)
		printf("Assumindo a Amplitude 5 e frequencia da portadora de 100Hz.\n");	
		CarrierFreq=100;
		Amp=5;
	elseif (nargin == 2)
		printf("Assumindo a frequencia da portadora de 100Hz.\n");	
		CarrierFreq=100;
	end
		

	%Tempo de Bit do Nosso NRZ
	nrzTs=0.001;
	%Numero de elementos do sinal de entrada
	nbrBits=length(bits);	
	%Tempo de Bit da Portadora
	CarrierTs=1/CarrierFreq;
	%Numero de Amostras por Segundo
	sampleBits=nrzTs/CarrierTs;
	%Tempo Fundamental
	TS=nrzTs/sampleBits;
	%Frequencia Fundamental de Saída, respeitando o Ritmo de Nyquist
	FS=2.2*(CarrierFreq/sampleBits);

	%Numero de elementos da nossa Base tempo.
	n=0:1/(nbrBits*FS-1):1;
	%Nosso conjunto que vai conter o sinal de saída
	myX= 1:1:nbrBits*FS;
	mynX= 1:1:nbrBits*FS;
	%Ciclo que vai criar a onda quadrada
	k=1;
	for i=1:nbrBits
		for  h=1:FS
			if( bits(i) == 1)
				myX(k)=Amp;
				mynX(k)=0;
				k++;
			else
 				myX(k)=0;
 				mynX(k)=Amp;
 				k++;
			end
		end
	end
	%Grafico
	%plot(n,myX);
	%axis([0 (FS*nbrBits) (-Amp-2) (Amp+2)]);

end