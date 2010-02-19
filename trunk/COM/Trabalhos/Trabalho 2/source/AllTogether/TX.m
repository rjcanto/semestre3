function [Y]=TX(signal,SNR,type,FS,Fc)
    switch type
     case 1
        Y=tx1(signal,SNR);
      case 2
        Y=tx2(signal,SNR,FS,Fc);
    end
end 