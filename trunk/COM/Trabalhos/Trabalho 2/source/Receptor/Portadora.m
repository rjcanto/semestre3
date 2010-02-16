function [signal,FS] = Portadora()
    TS=1/(10000-1);
    FS=10000;
	t=0:TS:1;
    signal=cos(2*pi*FS*t);
end