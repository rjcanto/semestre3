%
%Precisa de ser revisto
%
function [result]= correlador(Signal,Tb,FS,Modulation)
    bitrate=length(Tb)/10;    
    [a,FS]=Portadora(length(Tb));
    
    bitsLen=length(Signal)/bitrate;
    tmpY=zeros(1,bitrate);
    result=zeros(1,bitsLen);

    for i=0:bitsLen-1
        count=bitrate;
        while (count>0)
            idx=i*bitrate+count;
            tmpY(idx)=Signal(count);
            count=count-1;
        end

        Y=sum(tmpY.*a);
        result(i+1)=decisor(Y,tmpY(1),Tb,Modulation);
    end
end