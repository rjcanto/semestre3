function [FS,mySignal] = codificador(signal,A,B)
	if(nargin == 0)
		printf("É necessário mais argumentos.\n");
		return;
	elseif(nargin >3)
		printf("Têm argumentos a mais.\n");
		return;
	end
	
	fo=10;
	Amp=5;
	[FS,Xt,nXt]=NRZ(signal,Amp,fo);
	FS=FS*length(signal)-1;
	t=0:1/FS:1;
	aT=cos(2*pi*fo*t);

	x1T = Xt  .*(A* aT);
	x2T = nXt  .*(B* aT);
	mySignal=x1T + x2T;

end