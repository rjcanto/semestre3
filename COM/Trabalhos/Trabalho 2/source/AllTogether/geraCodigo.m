function [sinal_out] = geraCodigo(sinal)
%Função que recebe um sinal digital codifica a mesma segundo um código 11,4
%e devolve o sinal já codificado

%nº de bits de mensagem
numBits=4;

%normalização do sinal para ter ser multiplo de 4 bits
i = rem(numBits - rem(length(sinal),numBits),numBits);

while (i>0)
   sinal = horzcat(sinal,[0]); 
   i=i-1;
end
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
%Função que recebe o código de 4 bits a transmitir e devolve o código de 11 bits já codificado

%         [M0,M1,M2,M3,    B1,B2,B3,B4,B5,B6,B7]
geradora=[[1 0 0 0          1 1 0 1 0 0 1]
          [0 1 0 0          1 1 1 0 1 1 0]
          [0 0 1 0          1 0 1 1 0 1 0]
          [0 0 0 1          0 1 1 1 1 0 1]];
 
codigo = mod(mensagem * geradora,2);
          
% N Bits de Mensagem											
% K bits de mensagem				Q Bits de Código							
% M3	M2	M1	M0	M0+M1+M2	M0+M1+M3	M1+M2+M3	M0+M2+M3	M1+M3	M1+M2	M0+M3	dH
% 0	0	0	0	0	0	0	0	0	0	0	0
% 0	0	0	1	1	1	0	1	0	0	1	5
% 0	0	1	0	1	1	1	0	1	1	0	6
% 0	0	1	1	0	0	1	1	1	1	1	7
% 0	1	0	0	1	0	1	1	0	1	0	5
% 0	1	0	1	0	1	1	0	0	1	1	6
% 0	1	1	0	0	1	0	1	1	0	0	5
% 0	1	1	1	1	0	0	0	1	0	1	6
% 1	0	0	0	0	1	1	1	1	0	1	6
% 1	0	0	1	1	0	1	0	1	0	0	5
% 1	0	1	0	1	0	0	1	0	1	1	6
% 1	0	1	1	0	1	0	0	0	1	0	5
% 1	1	0	0	1	1	0	0	1	1	1	7
% 1	1	0	1	0	0	0	1	1	1	0	6
% 1	1	1	0	0	0	1	0	0	0	1	5
% 1	1	1	1	1	1	1	1	0	0	0	8

end

