function [sinal_out] = geraCodigo(sinal)
%Fun��o que recebe um sinal digital codifica a mesma segundo um c�digo 11,4
%e devolve o sinal j� codificado

%n� de bits de mensagem
numBits=4;

i=1;
k=0;
aux =[0,0,0,0];
sinal_out=[];
while (i*k < length(sinal))
    for i=1:numBits
        aux(i)=sinal(numBits*k+i);
    end
    sinal_out = horzcat(sinal_out,codificaBloco(aux));
    k = k+1;
end
end

function [codigo] = codificaBloco(mensagem)
%Fun��o que recebe o c�digo de 4 bits a transmitir e devolve o c�digo de 11
%bits j� codificado
%         [M0,M1,M2,M3,    B1,B2,B3,B4,B5,B6,B7]
geradora=[[1 0 0 0          1 1 0 1 0 0 1]
          [0 1 0 0          1 1 1 0 1 1 0]
          [0 0 1 0          1 0 1 1 0 1 0]
          [0 0 0 1          0 1 1 1 1 0 1]];
codigo = mod(mensagem * geradora,2);
end

