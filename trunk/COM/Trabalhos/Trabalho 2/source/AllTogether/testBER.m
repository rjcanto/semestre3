function [OutSignal]=testBER(InSignal)
    Fo=10000;
    xSNR=0:0.1:10;
    BER1=zeros(1,length(xSNR));
    BER2=BER1;
    BER3=BER2;
    BER4=BER3;
    i=1;
        [signal,FS,TB]=emissor(InSignal,Fo,'ook');
    for val=xSNR
        [Xsignal]=TX(signal,val,1,length(TB));
        OutSignal=receptor(Xsignal,FS,TB,'ook');
        BER1(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    figure;

    plot(xSNR,BER1);
        title('OOK em tx1');
    xlabel('SNR (Unidades Lineares)');
    ylabel('BER');
    i=1;
 
    i=1;
	for val=xSNR
        [Xsignal]=TX(signal,val,2,length(TB));
        OutSignal=receptor(Xsignal,FS,TB,'ook');   
        BER3(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    figure;
    plot(xSNR,BER3);
        title('OOK em tx2');
    xlabel('SNR (Unidades Lineares)');
    ylabel('BER');

    i=1;
    [signal,FS,TB]=emissor(InSignal,Fo,'psk');
    for val=xSNR
        [Xsignal]=TX(signal,val,1,length(TB));
        OutSignal=receptor(Xsignal,FS,TB,'psk');   
        BER2(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    figure;
    plot(xSNR,BER2);
    title('PSK em tx1');
    xlabel('SNR (Unidades Lineares)');
    ylabel('BER');


    i=1;
    for val=xSNR
        [Xsignal]=TX(signal,val,2,length(TB));
        OutSignal=receptor(Xsignal,FS,TB,'psk');   
        BER4(i)=BER(InSignal,OutSignal);
        i=i+1;
    end        
    figure;
    plot(xSNR,BER4);
    title('PSK em tx2');        
    xlabel('SNR (Unidades Lineares)');
    ylabel('BER');

end