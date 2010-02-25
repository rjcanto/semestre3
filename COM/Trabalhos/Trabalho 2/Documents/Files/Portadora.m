function [signal,FS] = Portadora()
    %a(t) = cos(2*pi*10000t) do 1º Trabalho
    FS=10000;
    TS=1/(FS-1);
    t=0:TS:1;
    signal=cos(2*pi*FS*t);
end