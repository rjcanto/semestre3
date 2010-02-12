function [xT,TS]= receptor(signal,FS)
    carrierFS=10000;
    Fo=FS/2.2 - carrierFS;
    %Filtro PassaBaixo/PassaBanda
    TS=1/carrierFS;
    yT=sinc(TS);
    yF=fft(yT);

    wF=signal.*yF;

    xT=ifft(wF);
    %analise do sinal
    figure('name','Sinal à Saída do Receptor.');
    my_analysis(xT,Fo);
    %wavplay(xT,Fo);
end