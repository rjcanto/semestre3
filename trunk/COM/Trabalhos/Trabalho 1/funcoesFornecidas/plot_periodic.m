%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% 
%
% plot_periodic.m
% Script para executar o desenho de sinais periódicos.
%

% Remover todas as variáveis de memória.
clear all

% Fechar todas as janelas de gráficos.
close all

%definir frequencia
f=2;

% Criar o vector de pontos, tendo em atencao a frequencia do sinal 
% que se pretende representar (Teo Nyquist)
t = -2 : 0.01 : 2;			

% Definir a amplitude
A = 3;

% Definir o offset.
B = 2;

% Aplicar a expressão do sinal.
x = B + A * cos( 2*pi*f*t  );
y = 2*x + 5;

% Desenhar o sinal x.
plot( t, x );

% Colocar uma grelha sobre o desenho.
grid on;

% Labels e títulos.
xlabel(' Tempo ');
ylabel(' Amplitude ');
title(   [' Sinusóide com offset  x(t)=2 + 3cos( 2\pi' num2str(f)  't  ) ']  );

% Desenhar dois gráficos na mesma figura.
% Sinal original e transformado.
figure;
subplot(2,1,1); plot( t, x ); xlabel(' Tempo '); ylabel(' Amplitude ');
grid on;      title(   [' x(t)=2 + 3cos( 2\pi' num2str(f)  't  ) ']  );
subplot(2,1,2); plot( t, y ); xlabel(' Tempo '); ylabel(' Amplitude ');
grid on;      title(' Sinal y(t)=2x(t)+5');