function [yF,FS]= emissor(signal,Fo)
    carrierFs=10000;
    FS=2.2*carrierFs;
    t=0:1/(FS-1):1;

    %Sinal da Portadora
    aT=cos(2*pi*carrierFs*t);

    yT=aT.*signal;
    yF=fft(yT);
    
    figure;
    my_analysis(yT,FS); 
end