%
%Precisa de ser revisto
%
function [result]= correlador(Signal,FS,TB,Modulation)

    bitsLen=FS;    
    bitsnbr=length(Signal)/FS; %6 bits
    t=0:1/(bitsLen-1):1;

    tmpY=zeros(1,bitsLen);
    result=zeros(1,bitsnbr);


    for i=1:bitsnbr
        count=1;
        while (count <= bitsLen )
            idx=(i-1)*bitsLen+count;
            tmpY(count)=Signal(idx);
            count=count+1;
        end
        Y=sum(tmpY.*cos(2*pi*10000*t));
        result(i)=decisor(Y,bitsLen,Modulation);
    end



    result
%         figure
%         plot(result)
%         axis([0,20,-5,5])
%         title('Sinal result');
end