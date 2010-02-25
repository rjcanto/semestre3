function [OutSignal]=main(InSignal,Fo,Mod,t,Fc,SNR)
    %SNR=10;
    type=t;
	%InSignal
    %InSignal=Normaliza(InSignal);
    
     CodedSignal = geraCodigo(InSignal);
%     CodedSignal=InSignal;
    [signal,FS]=emissor(CodedSignal,Fo,Mod);
    
    %construção do array de tempos
%     TB=0.001;
%     samplesBit = length(0:1/(FS-1):TB);
%     n = length(signal)/samplesBit;
%     t = 0:(TB*n)/(samplesBit*n-1):TB*n;
%     figure;
%     subplot(2, 1, 1);
%     plot(t,signal);
%     ylabel('sinal de entrada');
     
    [signal]=TX(signal,SNR,type,FS,Fc);
%     subplot(2, 1, 2);
%     plot(t,signal);
%     ylabel('sinal depois de TX');

     
    OutSignal=receptor(signal,FS,Mod);
    OutSignal=descodificador(OutSignal);

   % BER(InSignal,OutSignal)
end 