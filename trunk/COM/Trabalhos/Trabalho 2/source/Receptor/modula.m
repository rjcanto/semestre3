function [mysignal]=modula(signal,amplierFactor,RS)
	%timebase=0:1/(RS-1):1;
    %aT=cos(2*pi*CarrierFreq*(timebase));
    aT=Portadora(10000*RS);
    length(signal)
    length(aT)
	mysignal= amplierFactor*signal*(aT);
end