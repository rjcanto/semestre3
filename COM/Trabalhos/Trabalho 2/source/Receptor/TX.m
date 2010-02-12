function [Y]=TX(signal,SNR,type)
    switch type
     case 1
        Y=tx1(signal,SNR);
      case 2
        Y=tx2(signal,SNR);
    end
end 