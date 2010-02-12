function [signal,FS] = Portadora(FS)
    TS=1/(FS-1);
    t=0:TS:1;
    signal=cos(2*pi*FS*t);
end