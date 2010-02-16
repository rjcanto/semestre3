function [mysignal]=modulaQAM(signal,amplierFactor,CarrierFreq,timebase)
    c=cos(2*pi*CarrierFreq*timebase);
    s=-sin(2*pi*CarrierFreq*timebase);
	mysignal= signal.*(amplierFactor*c) + signal.*(amplierFactor*s);
end