function []=BERValues(InSignal,SNR)
    Fo=10000;
    Fc=8000;
    
    display( 'OOK em Tx1');
    [signal,FS]=emissor(InSignal,Fo,'ook');
    [Xsignal]=TX(signal,SNR,1,FS,Fc);
    OutSignal=receptor(Xsignal,FS,'ook');
    BERvalue=BER(InSignal,OutSignal)
    
    display( 'OOK em Tx2');
    [signal,FS]=emissor(InSignal,Fo,'ook');
    [Xsignal]=TX(signal,SNR,2,FS,Fc);
    OutSignal=receptor(Xsignal,FS,'ook');
    BERvalue=BER(InSignal,OutSignal)
    
    display( 'PSK em Tx1');
    [signal,FS]=emissor(InSignal,Fo,'psk');
    [Xsignal]=TX(signal,SNR,1,FS,Fc);
    OutSignal=receptor(Xsignal,FS,'psk');
    BERvalue=BER(InSignal,OutSignal)
   
    display( 'PSK em Tx2');
    [signal,FS]=emissor(InSignal,Fo,'psk');
    [Xsignal]=TX(signal,SNR,2,FS,Fc);
    OutSignal=receptor(Xsignal,FS,'psk');
    BERvalue=BER(InSignal,OutSignal)
end