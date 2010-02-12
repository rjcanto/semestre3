function sistema(signal,fo)
    %Codificador NRZ
    [nrzFS,nrzmyX,nrzmynX,nrzn]=NRZ(signal,5,fo);
    %Modelação OOK
    [ookFS,ookSignal,ookn]=OOK(signal,1,0,fo);
    %Modelação PSK
    [pskFS,pskSignal,pskn]=PSK(signal,1,-1,fo);
    %Recuperação do x(t)
    cT = modula(pskSignal,1,fo,pskn);
    
    figure;
    subplot(4,1,1);
    plot(nrzn,nrzmyX);
    title('Sinal após condificação NRZ');
    subplot(4,1,2);
    plot(ookn,ookSignal);
    title('Sinal após modulação OOK');    
    subplot(4,1,3);
    plot(pskn,pskSignal);
    title('Sinal após modulação PSK');
    subplot(4,1,4);
    plot(pskn, cT);
    title('Sinal c(t), ou o x(t) recuperado');
end