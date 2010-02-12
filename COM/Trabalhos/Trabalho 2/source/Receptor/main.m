function [OutSignal]=main(InSignal,Fo,Mod)
    SNR=0;
    type=1;

    
    [signal,FS,TB]=emissor(InSignal,Fo,Mod);
    
    signal=TX(signal,SNR,type);
    
    OutSignal=receptor(signal,FS,TB,Mod);
    
%     figure;
%     subplot(4,1,1);
%     plot(FS,signal);
%     title('Sinal de Entrada');
%     subplot(4,1,4);
%     plot(signal,FS);
%     title('Sinal c(t), ou o x(t) recuperado');
    
    
    return

end 