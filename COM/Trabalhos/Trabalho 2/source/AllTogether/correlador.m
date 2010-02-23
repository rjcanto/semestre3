function [result]= correlador(Signal,FS,Modulation)
    [TB,Amp]=NRZValues();
    %construção do array de tempos
    bitsLen = length(0:1/(FS-1):TB);
    bitsnbr = length(Signal)/bitsLen;
    t = 0:(TB*bitsnbr)/(bitsLen*bitsnbr-1):TB*bitsnbr; 
    
    Signal=Signal.*cos(2*pi*10000*t);
    tmpY=zeros(1,bitsLen);
    result=zeros(1,bitsnbr);
    %plot(t,Signal);
    for i=1:bitsnbr
        count=1;
        while (count <= bitsLen )
            idx=(i-1)*bitsLen+count;
            tmpY(count)=Signal(idx);
            count=count+1;
        end
         %c = sum(signal.*(cos(2*pi*2000*tx)));
         
        Y=sum(tmpY);
        result(i)=decisor(Y,Modulation);
    end
end