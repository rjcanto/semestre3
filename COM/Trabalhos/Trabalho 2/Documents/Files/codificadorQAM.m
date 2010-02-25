function [FS,mySignal,t] = codificador(signal,A,B,Fo)
	if(nargin == 0)
		printf('É necessário mais argumentos.\n');
		return;
	elseif(nargin >4)
		printf('Têm argumentos a mais.\n');
		return;
	end
	
	[TB,Amp]=NRZValues();
	[FS,Xt,nXt,n]=NRZ(signal,Amp,TB,Fo);
    t=n;
	mySignal=modulaQAM(Xt,nXt,Fo,t);
end