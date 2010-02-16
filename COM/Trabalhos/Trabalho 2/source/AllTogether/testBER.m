function [OutSignal]=testBER(InSignal)
    Fo=10000;
    xSNR=0.1:0.2:10;
    BER1=zeros(1,length(xSNR));
    BER2=BER1;
    BER3=BER2;
    BER4=BER3;
    i=1;
        [signal,FS,TB]=emissor(InSignal,Fo,'ook');
    for SNR=0.1:0.2:10
        signal=TX(signal,SNR,1,length(TB));
        OutSignal=receptor(signal,FS,TB,'ook');
        BER1(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    i=1;
    [signal,FS,TB]=emissor(InSignal,Fo,'psk');
    for SNR=0.1:0.2:10

        signal=TX(signal,SNR,1,length(TB));
        OutSignal=receptor(signal,FS,TB,'ook');   
        BER2(i)=BER(InSignal,OutSignal);
        i=i+1;
    end 
    i=1;
    [signal,FS,TB]=emissor(InSignal,Fo,'ook');
	for SNR=0.1:0.2:10
        signal=TX(signal,SNR,2,length(TB));
        OutSignal=receptor(signal,FS,TB,'ook');   
        BER3(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    i=1;
	[signal,FS,TB]=emissor(InSignal,Fo,'psk');
    for SNR=0.1:0.2:10
    
        signal=TX(signal,SNR,2,length(TB));
        OutSignal=receptor(signal,FS,TB,'ook');   
        BER4(i)=BER(InSignal,OutSignal);
        i=i+1;
    end        
    
    figure;
    subplot(4,1,1);
    plot(xSNR,BER1);
    title('BER TX1 OOK');
    subplot(4,1,2);
    plot(xSNR,BER2);
    title('BER TX1 PSK');
    subplot(4,1,3);
    plot(xSNR,BER3);
    title('BER TX2 OOK');
    subplot(4,1,4);
    plot(xSNR, BER4);
    title('BER TX2 PSK');

figure ;plot(xSNR,BER4)    ;


end