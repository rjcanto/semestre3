%Exercicio 1.d.
%Seja o sistema definido por y[n]. Aplique este sistema a sinusóides e aos 
%sinais de áudio disponibilizados com o enunciado. Recorrendo à função 
%analysis, bem como a outros testes, identifique o tipo de filtragem 
%realizado por este sistema.

function [] = t1d()
    close all;
    x=wavread('fala1.wav');
    y=(1/3)*x + (1/3)*(x - 1) + (1/3)*(x - 2);
    sound(y,11054);
    %reduzir a amplitude e adicionar o mesmo sinal com atraso
    %provoca distroção do sinal e perca de nitidez
    %
    %No grafico nota-se que existe uma componente DC no sinal.
    figure;
    analysis(x,0);

    figure;
    analysis(y,0);

    
end
