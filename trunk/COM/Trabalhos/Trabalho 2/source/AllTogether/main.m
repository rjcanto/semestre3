function [OutSignal]=main(InSignal,Fo,Mod)
    SNR=-2000;
    type=2;
    FS=10000;

    InSignal
    [signal,FS,TB]=emissor(InSignal,Fo,Mod);
    %signal=TX(signal,SNR,type,FS);
    OutSignal=receptor(signal,FS,TB,Mod);

    BER(InSignal,OutSignal)

    
    return

end 