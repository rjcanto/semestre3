%
%Precisa de ser revisto
%
function [result]= correlador(Signal,FS,TB,Modulation)
    bitsLen=FS;    
    bitsnbr=length(Signal)/FS;
    t=0:1/(bitsLen-1):1;
    Signal=Signal.*cos(2*pi*10000*TB);
    tmpY=zeros(1,bitsLen);
    result=zeros(1,bitsnbr);
    
    for i=1:bitsnbr
        count=1;
        while (count <= bitsLen )
            idx=(i-1)*bitsLen+count;
            tmpY(count)=Signal(idx);
            count=count+1;
        end
        Y=sum(tmpY);
        result(i)=decisor(Y,FS,Modulation);
    end
end