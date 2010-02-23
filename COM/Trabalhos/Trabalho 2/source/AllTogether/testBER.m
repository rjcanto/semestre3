function [OutSignal]=testBER(InSignal)
    Fo=10000;
    Fc=15000;
    xSNR=-20:0.1:20;
    BER1=zeros(1,length(xSNR));
    BER2=BER1;
    BER3=BER2;
    BER4=BER3;
    i=1;
    display( 'OOK em Tx1');
    [signal,FS]=emissor(InSignal,Fo,'ook');
    for val=xSNR
        [Xsignal]=TX(signal,val,1,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'ook');
        BER1(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    LinearRegressionPlot(xSNR,BER1,'OOK em Tx1');
    
    display( 'OOK em Tx2');
    [signal,FS]=emissor(InSignal,Fo,'ook');
    i=1;
	for val=xSNR
        [Xsignal]=TX(signal,val,2,FS,Fc);
        OutSignal=receptor(Xsignal,FS,'ook');   
        BER3(i)=BER(InSignal,OutSignal);
        i=i+1;
    end
    
    LinearRegressionPlot(xSNR,BER3,'OOK em Tx2');
    
    display( 'PSK em Tx1');
    i=1;
    [signal,FS]=emissor(InSignal,Fo,'psk');
%    figure;
%    plot(signal);
    for val=xSNR
        [Xsignal]=TX(signal,val,1,Fo,Fc);
        OutSignal=receptor(Xsignal,FS,'psk');   
        BER2(i)=BER(InSignal,OutSignal);
        i=i+1;
    end

    LinearRegressionPlot(xSNR,BER2,'PSK em Tx1');
    
    display( 'PSK em Tx2');
    i=1;
    for val=xSNR
        [Xsignal]=TX(signal,val,2,Fo,Fc);
        OutSignal=receptor(Xsignal,FS,'psk');   
        BER4(i)=BER(InSignal,OutSignal);
        i=i+1;
    end  

    LinearRegressionPlot(xSNR,BER2,'PSK em Tx2');

end