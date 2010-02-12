% Recorrendo à função awgn do MATLAB, escreva a função tx1 que realize
% um canal de transmissão, tal que este some ruído branco e gaussiano ao 
% sinal de entrada, com relação sinal-ruído especificada como parâmetro.
%
function [Y]=tx1(signal,SNR)
    Y=awgn(signal,SNR);
end 