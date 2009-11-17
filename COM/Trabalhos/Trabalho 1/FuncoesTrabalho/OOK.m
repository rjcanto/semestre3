function OOK(signal,paramA,paramB)
	if(nargin == 0)
		printf("É necessário mais argumentos.\n");
		return;
	elseif(nargin >3)
		printf("Têm argumentos a mais.\n");
		return;
	elseif (nargin == 1)
		printf("Assumindo o valor 1 do paramA e o valor 0 no paramB.\n");	
		paramA=1;
	end
	paramB=0;	
	
	[FS,mySignal]=codificador(signal,paramA,paramB);
	t=0:1/FS:1;
	
	figure
	plot(t,mySignal)
	title("Sinal OOK");	
	grid on;

end