function []=testeEx1()
    FS=100;
    TS=1/(FS-1);
    
    time=0:TS:1;

    at=cos(2*pi*FS*time);

    signal1=tx1(at,0);
    signal2=tx2(at,0,FS);
    
    figure;
    plot(time,signal1);
    figure;
    plot(time,signal2);


end