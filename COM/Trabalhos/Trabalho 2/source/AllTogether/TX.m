function [Y]=TX(signal,SNR,type,FS)
    switch type
     case 1
        Y=tx1(signal,SNR);
      case 2
        Y=tx2(signal,SNR,FS);
    end
end 