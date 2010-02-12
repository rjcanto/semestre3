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
    %http://www.bgfl.org/bgfl/custom/resources_ftp/client_ftp/ks2/music/piano/index.htm
    
    if (( mod(n,2)) ~= 0 )
       fprintf('O argumento tem que ser um conjunto par.\n');
       help sintetizador;
       return;
    end

    JAQUES=[1 0.3 2 0.3 3 0.3 1 0.3 1 0.3 2 0.3 3 0.3 1 0.3 3 0.3 4 0.3 5 0.5 3 0.3 4 0.3 5 0.5 5 0.3 6 0.3 5 0.3 4 0.3 3 0.3 1 0.3 5 0.3 6 0.3 5 0.3 4 0.3 3 0.3 1 0.3 1 0.3 5 0.3 1 0.5 1 0.3 5 0.3 1 0.5];    
    JINGLE=[3 0.4 3 0.4 3 0.8 3 0.4 3 0.4 3 0.8 3 0.4 5 0.4 1 0.4 2 0.4 3 1.2 4 0.4 4 0.4 4 0.4 4 0.4 4 0.4 3 0.4 3 0.4 3 0.4 3 0.4 2 0.4 2 0.4 3 0.4 2 1.2]
    n=JAQUES;
    
    base_frq_Do=4400;
    
    for i=1:2:length(n)
        exp=(n(i))/12;
        j=i+1;
        time=n(j);
        if (exp ~= 0)
            base_frq=base_frq_Do*power(2,exp);
            
        else
            base_frq=0;
        end
        
        [s,fs]=t1_nota(2,base_frq,time);
       sound(s,fs);
    end
end