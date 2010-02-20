function [FS,mySignal]=PSK(signal,paramA,paramB,fo)
	if(nargin == 0)
		fprintf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		fprintf('Têm argumentos a mais.\n');
		return;
	elseif (nargin == 1)
		fprintf('Assumindo o valor 1 do paramA e o valor -1 no paramB.\n');	
		paramA=1;
		paramB=-1
	elseif (nargin == 2)
		fprintf('Assumindo o valor -paramA para o paramB.\n');	
        paramB=-paramA;
	else
		if (paramB - paramA > 0)
			paramB = -paramB;
		end
	end
	[FS,mySignal]=codificador(signal,paramA,paramB,fo);
end