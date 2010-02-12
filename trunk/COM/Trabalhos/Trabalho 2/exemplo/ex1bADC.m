function [bits] = ex1bADC(out , TSinal)
    %******************
    %execicio 3 a)
    %******************
    idx = 0; index = 1; idx2 = 0;offset = 0;
    zerozero = 0; zeroum = 0; umzero = 0; umum = 0;
    FS = 20000;
    count = 0;
    tx = 0 : 1/FS : TSinal;

    bits = zeros([1 , ceil((length(out)/(length(tx))*2)/3)]);
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
            umzero = umzero + 1;
            count = count+1;       
       end
       
       if((s > 0) && (c < 0))           
            umum = umum + 1;
            count = count+1;
         
       end

       if((s < 0) && (c > 0))           
            zerozero = zerozero + 1;
            count = count+1;
       end
       
       if((s < 0) && (c < 0))           
            zeroum = zeroum + 1;
            count = count+1;
       end
       
       if(count == 3)
        if (zerozero > 1)
            idx = idx + 1;
            bits(idx) = 0;
            idx = idx + 1;
            bits(idx) = 0;
           zerozero = 0; zeroum = 0; umzero = 0; umum = 0;
        end
        if (umzero > 1)
            idx = idx + 1;
            bits(idx) = 1;
            idx = idx + 1;
            bits(idx) = 0;
           zerozero = 0; zeroum = 0; umzero = 0; umum = 0;
        end
        if (zeroum > 1)
            idx = idx + 1;
            bits(idx) = 0;
            idx = idx + 1;
            bits(idx) = 1;
           zerozero = 0; zeroum = 0; umzero = 0; umum = 0;
        end
        if (umum > 1)
            idx = idx + 1;
            bits(idx) = 1;
            idx = idx + 1;
            bits(idx) = 1;
           zerozero = 0; zeroum = 0; umzero = 0; umum = 0;
        end
        count = 0;
       end
    end
    end