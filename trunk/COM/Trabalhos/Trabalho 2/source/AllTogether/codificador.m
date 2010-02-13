function [FS,mySignal,t] = codificador(signal,A,B,Fo)
	if(nargin == 0)
		printf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		printf('Têm argumentos a mais.\n');
		return;
	end
	
	Amp=20;
	[FS,Xt,nXt,n]=NRZ(signal,Amp,Fo);
	%t=0:1/(FS-1):1;
    t=n;
	x1T = modula(Xt,A,Fo,t);
	x2T = modula(nXt,B,Fo,t);
	mySignal=x1T + x2T;
end