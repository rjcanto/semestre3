%Gera Som de Notas Musicais. 
%
%Input:
%   n= Array com as notas a serem geradas. Cada par de elementos referem-se
%   a uma nota (1 - 12) e o tempo a que essa nota toca.
%
%Output:
%   s: retorna o sinal gerado.
%
function [s]= sintetizador(n)
    for i=1:2:length(n)
        exp=(n(i))/12;
        j=i+1;
        time=n(j);
        if (exp ~= 0)
            base_frq=523.25*power(2,exp);
        else
            base_frq=0;
        end
        
        [s,fs]=t1_nota(2,base_frq,time);
       sound(s,fs);
    end
end