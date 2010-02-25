function [mySignal,FS] = codificador(signal,A,B,Fo)
	if(nargin == 0)
		printf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		printf('Têm argumentos a mais.\n');
		return;
	end
	
	[TB,Amp]=NRZValues();
	[Xt,nXt,FS]=NRZ(signal,Amp,TB,Fo);
    %construção do array de tempos
    samplesBit = length(0:1/(FS-1):TB);
    n = length(Xt)/samplesBit;
    t = 0:(TB*n)/(samplesBit*n-1):TB*n;
    
	x1T = modula(Xt,A,Fo,t);
	x2T = modula(nXt,B,Fo,t);
	mySignal=x1T + x2T;
    %plot(t,mySignal);
end