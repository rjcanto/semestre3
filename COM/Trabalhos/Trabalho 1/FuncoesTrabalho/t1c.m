%Exercicio 1.c.
%Identifique a funcionalidade da função chirp do MATLAB. Aplique a função
%analysis aos sinais produzidos pela função chirp e explique o formato dos 
%gráficos obtidos.

%O sinal chirp corresponde a uma sinusóide cuja frequencia varia no tempo.
%Vantagem: permite estipular o intervalo de frequencia a trabalhar.
%Desvantagem: Não deve ser utilizado por métodos que necessitem de entradas
%de sinal do tipo "ruido branco".

function [] = t1c()
    close all; 
    %recebe um sinal.
    [signal,fs]=t1_nota(1,440,0.005);
    %efectuado um varrimento ao sinal
    t=0:0.001:0.01;
    s_chirp=chirp(t,10);
    %efectuado a analisys do sinal anterior.
    figure
    analysis(s_chirp,0);

    %Gráficos Gerados:
    %Gráfico de Vector:
    %Verifica-se o desempenho do sinal ao longo do tempo.
    %Grafico de Espectro:
    %Grafico de Espectrograma:
    
end
