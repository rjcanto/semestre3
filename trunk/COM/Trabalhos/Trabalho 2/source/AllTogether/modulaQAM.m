function [mysignal]=modulaQAM(signal,nsignal,CarrierFreq,timebase)

    phi=0;
    c=cos(phi*timebase);
    s=-sin(phi*timebase);
    
	mysignal= signal.*c + nsignal.*s;
end