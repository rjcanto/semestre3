function [OutSignal]=testBER(InSignal)
    Fo=10000;

    for SNR=0.1:0.2:10
        [signal,FS,TB]=emissor(InSignal,Fo,'ook');
        signal=TX(signal,SNR,1,FS);
        OutSignal=receptor(signal,FS,TB,'ook');   
    end
    for SNR=0.1:0.2:10
        [signal,FS,TB]=emissor(InSignal,Fo,'psk');
        signal=TX(signal,SNR,1,FS);
        OutSignal=receptor(signal,FS,TB,'ook');   
    end    
    for SNR=0.1:0.2:10
        [signal,FS,TB]=emissor(InSignal,Fo,'ook');
        signal=TX(signal,SNR,2,FS);
        OutSignal=receptor(signal,FS,TB,'ook');   
    end
    for SNR=0.1:0.2:10
        [signal,FS,TB]=emissor(InSignal,Fo,'psk');
        signal=TX(signal,SNR,2,FS);
        OutSignal=receptor(signal,FS,TB,'ook');   
    end        



end