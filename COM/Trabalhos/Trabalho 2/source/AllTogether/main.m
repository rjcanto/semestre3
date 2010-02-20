function [OutSignal]=main(InSignal,Fo,Mod,t,Fc)
    SNR=20;
    type=t;
	%InSignal
    InSignal=Normaliza(InSignal);
    
%      CodedSignal = geraCodigo(InSignal);
   CodedSignal=InSignal;
    [signal,FS]=emissor(CodedSignal,Fo,Mod);
    
    %construção do array de tempos
%     TB=0.001;
%     samplesBit = length(0:1/(FS-1):TB);
%     n = length(signal)/samplesBit;
%     t = 0:(TB*n)/(samplesBit*n-1):TB*n;
%     plot(t,signal);
     
    [signal]=TX(signal,SNR,type,FS,Fc);
    
% 
%       figure;
%       plot(t,signal);
     
    OutSignal=receptor(signal,FS,Mod);
%     OutSignal=descodificador(OutSignal);

   % BER(InSignal,OutSignal)
end 