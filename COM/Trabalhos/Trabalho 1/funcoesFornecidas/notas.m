%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
%
% notas.m
% Função de teste. Geração das notas musicais.
%
function notas()

% Remover da memoria todas as variaveis.
clear all;

% Fechar todas as janelas com figuras.
close all;

% Definir a frequencia de amostragem (em Hz).
Fs = 8192;

% A duracao do sinal (em segundos).
NSec = 1;

% A frequencia inicial (em Hz).
f = 440;

% O vector com o numero total de pontos.
n = 1 : 1 : Fs*NSec;

for i=1 : 8    
    
    % Calcular a frequencia digital    
    W = 2*pi*(f/Fs);
    
    % Gerar a sinusoide com a frequencia digital
    Signal = cos( W * n );
    
    % Mensagem
    fprintf('(%d) - Sinusoide de frequencia %.2f Hz durante %.2f segundos \n', i, f, NSec );
    
    % Reproduzir o sinal
    wavplay( Signal, Fs );

    % Actualizar a frequencia 
    f = f * power(2,1/12);    
    
    % Reproduzir silencio
    wavplay( zeros(1, round((Fs*NSec)/100)), Fs );
    
  %  pause
end

