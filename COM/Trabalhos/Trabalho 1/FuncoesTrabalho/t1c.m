%Exercicio 1.c.
%Identifique a funcionalidade da função chirp do MATLAB. Aplique a função
%analysis aos sinais produzidos pela função chirp e explique o formato dos 
%gráficos obtidos.

%O sinal chirp corresponde a uma sinusóide cuja frequencia varia no tempo.
%Vantagem: permite estipular o intervalo de frequencia a trabalhar.
%Desvantagem: Não deve ser utilizado por métodos que necessitem de entradas
%de sinal do tipo "ruido branco".

function t1c()
    close all; 
    %Escollha de uma frequencia de amostragem
    fs=1000;
    %efectuado um varrimento ao sinal em 1 segundo
    t=0:1/fs:1;
    s_chirp=chirp(t,fs);
    %efectuado a analisys do sinal anterior.
    figure
    analysis(s_chirp,fs);
end

