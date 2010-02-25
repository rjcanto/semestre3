function [BerValuesArray]=BERValues(InSignal)
    Fo=10000;
    Fc=10000;
    SNR=0:10;
    BerValuesArray = zeros(5,length(SNR));
    
    for i=1:length(SNR)
        BerValuesArray(1,i)=SNR(i);
        
%         display( 'OOK em Tx1');
        [signal,FS]=emissor(InSignal,Fo,'ook');
        [Xsignal]=TX(signal,SNR(i),1,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'ook');
        BerValuesArray(2,i)=BER(InSignal,OutSignal)/length(InSignal);

%         display( 'OOK em Tx2');
        [signal,FS]=emissor(InSignal,Fo,'ook');
        [Xsignal]=TX(signal,SNR(i),2,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'ook');
        BerValuesArray(3,i)=BER(InSignal,OutSignal)/length(InSignal);

%         display( 'PSK em Tx1');
        [signal,FS]=emissor(InSignal,Fo,'psk');
        [Xsignal]=TX(signal,SNR(i),1,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'psk');
        BerValuesArray(3,i)=BER(InSignal,OutSignal)/length(InSignal);

%         display( 'PSK em Tx2');
        [signal,FS]=emissor(InSignal,Fo,'psk');
        [Xsignal]=TX(signal,SNR(i),2,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'psk');
        BerValuesArray(4,i)=BER(InSignal,OutSignal)/length(InSignal);
    end;
end