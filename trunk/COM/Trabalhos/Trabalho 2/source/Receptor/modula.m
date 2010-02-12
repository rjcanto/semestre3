function [mysignal]=modula(signal,amplierFactor,CarrierFreq,RS)
	timebase=0:1/(RS-1):1;
    aT=cos(2*pi*CarrierFreq*(timebase));
	mysignal= signal.*(amplierFactor*aT);
end