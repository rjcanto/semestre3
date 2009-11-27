function [FS,mySignal,t] = codificador(signal,A,B,fo)
	if(nargin == 0)
		printf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		printf('Têm argumentos a mais.\n');
		return;
	end
	
	Amp=5;
	[FS,Xt,nXt,n]=NRZ(signal,Amp,fo);
	t=0:1/(FS-1):1;
	x1T = modula(Xt,A,fo,t);
	x2T = modula(nXt,B,fo,t);
	mySignal=x1T + x2T;
end