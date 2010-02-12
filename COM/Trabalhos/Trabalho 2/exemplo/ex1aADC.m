function [bits] = ex1aADC(out , TSinal)
    %******************
    %execicio 3 a)
    %******************
    idx = 1; index = 1; idx2 = 0;offset = 0;
    FS = 20000;
    tx = 0 : 1/FS : TSinal;

    bits = zeros([1 , ceil((length(out)/(length(tx))*2))]);
    signal = zeros([1 , length(tx)]);
    
    while (idx < length(bits))
        idx2 = idx2 + 1;
        
       for inner = index : length(tx)*idx2;
          if(inner <= length(out))
                signal(inner-offset) = out(inner); 
          end
            index = index + 1;
       end
       
       offset = inner;
       
       c = sum(signal.*(cos(2*pi*2000*tx)));
       s = sum(signal.*(sin(2*pi*2000*tx)));
       
       
       if((s >= 0) && (c >= 0))
            bits(idx) = 1;
            idx = idx + 1;
            bits(idx) = 0;
       end
       if((s > 0) && (c < 0))
            bits(idx) = 1;
            idx = idx + 1;
            bits(idx) = 1;
       end
       if((s < 0) && (c > 0))
            bits(idx) = 0;
            idx = idx + 1;
            bits(idx) = 0;
       end
       if((s < 0) && (c < 0))
            bits(idx) = 0;
            idx = idx + 1;
            bits(idx) = 1;
       end
       idx = idx + 1;
    end
    end