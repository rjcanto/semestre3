function [mysignal]=modula(signal,amplierFactor,CarrierFreq, timebase)    
    aT=cos(2*pi*CarrierFreq*timebase);
	mysignal= signal.*(amplierFactor*aT);
end
