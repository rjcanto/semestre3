function [OutSignal]=main(InSignal,Fo,Mod)
    SNR=0;
    type=1;
	%InSignal
    [signal_F,FS,TB]=emissor(InSignal,Fo,Mod);
    signal_F=TX(signal_F,SNR,type,FS);
    OutSignal=receptor(signal_F,FS,TB,Mod);

    BER(InSignal,OutSignal)

end 