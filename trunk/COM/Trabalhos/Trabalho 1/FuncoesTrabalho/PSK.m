function PSK(signal,paramA,paramB)
	if(nargin == 0)
		printf("É necessário mais argumentos.\n");
		return;
	elseif(nargin >3)
		printf("Têm argumentos a mais.\n");
		return;
	elseif (nargin == 1)
		printf("Assumindo o valor 1 do paramA e o valor -1 no paramB.\n");	
		paramA=1;
		paramB=-1
	elseif (nargin == 2)
		printf("Assumindo o valor -paramA para o paramB.\n");	
	else
		if (paramA - paramB >= 0)
			paramB = -paramB;
		end
			
	end
	
	[FS,mySignal]=codificador(signal,paramA,paramB);
	t=0:1/FS:1;
	
	figure;
	plot(t,mySignal);
	title("Sinal PSK");	
	grid on;

end