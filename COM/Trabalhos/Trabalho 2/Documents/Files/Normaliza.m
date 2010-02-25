function [Signal] = Normaliza(Signal)

numBits=4;
%normalização do sinal para ser multiplo de 4 bits
i = rem(numBits - rem(length(Signal),numBits),numBits);

while (i>0)
   Signal = horzcat(Signal,[0]); 
   i=i-1;
end

end

