function [OutSignal]=main(InSignal,Fo,Mod,t,Fc)
    SNR=0;
    type=t;
	%InSignal
    [signal,FS,TB]=emissor(InSignal,Fo,Mod);
    [signal]=TX(signal,SNR,type,FS,Fc);
    OutSignal=receptor(signal,FS,TB,Mod)

    BER(InSignal,OutSignal)
end 