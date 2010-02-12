%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
%
% time2.m
% Função de teste.
%
function time2()

% Limpar a consola.
clc;

% Dimensão do vector.
vector_size = 50000;

% Sinusoide com vector_size pontos.
x = cos( (pi/100) * (1:1:vector_size) );

%-------------------------------------------------------------------------
% Concatenar elementos num vector - forma 1
currentTime = fix(clock);
%currentTime = [year month day hour minute seconds]
fprintf(' Forma 1 - Start at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));

% Vector inicial vazio.
v1 = [];
t0 = cputime;
for i=1 : vector_size
        v1 = [v1 x(i)];
end
t1 = cputime - t0;

currentTime = fix(clock);
fprintf(' Forma 1 - Stop  at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
%-------------------------------------------------------------------------

%-------------------------------------------------------------------------
% Concatenar elementos num vector - forma 2
currentTime = fix(clock);
%currentTime = [year month day hour minute seconds]
fprintf(' Forma 2 - Start at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));

% Vector inicial a zeros com a dimensão definida.
v2 = zeros(1, vector_size );
t0  = cputime;
for i=1 : vector_size
        v2(i) = x(i);
end
t2 = cputime - t0;


currentTime = fix(clock);
fprintf(' Forma 2 - Stop  at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
%-------------------------------------------------------------------------

fprintf(' Forma 1: %.4f [seg]    Forma 2: %.4f [seg] \n', t1, t2);



