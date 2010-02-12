%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
%
% time3.m
% Função de teste.
%
function time3()

% Limpar a consola.
clc;

% Dimensões da matriz.
NRows = 8000;
NCols = 6000;

% Criar a matriz com dimensoes matrix_size x matrix_size.
A = randn( NRows, NCols );

%-------------------------------------------------------------------------
% Forma 1.
s1 = 0;
currentTime = fix(clock);
%currentTime = [year month day hour minute seconds]
fprintf(' Forma 1 - Start at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
t0 = cputime;
for i=1 : NRows
    for j=1 : NCols
        s1 = s1 + A(i,j);
    end
end
t1 = cputime - t0;

currentTime = fix(clock);
fprintf(' Forma 1 - Stop  at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
%-------------------------------------------------------------------------


%-------------------------------------------------------------------------
% Forma 2.
s2 = 0;
currentTime = fix(clock);
%currentTime = [year month day hour minute seconds]
fprintf(' Forma 2 - Start at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
t0 = cputime;
for i=1 : NCols
    for j=1 : NRows
        s2 = s2 + A(j,i);
    end
end
t2 = cputime - t0;

currentTime = fix(clock);
fprintf(' Forma 2 - Stop  at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
%-------------------------------------------------------------------------


%-------------------------------------------------------------------------
% Forma 3.
s3 = 0;
currentTime = fix(clock);
%currentTime = [year month day hour minute seconds]
fprintf(' Forma 3 - Start at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
t0 = cputime;
for i=1 : NCols*NRows
    s3 = s3 + A(i);
end
t3 = cputime - t0;

currentTime = fix(clock);
fprintf(' Forma 3 - Stop  at %d:%d:%d \n', currentTime(4),...
    currentTime(5), currentTime(6));
%-------------------------------------------------------------------------

% Comparar os resultados dos tres processos.
fprintf('s1=%d  s2=%d  s3=%d \n', s1, s2, s3 );
fprintf('t1=%.4f [seg]  t2=%.4f [seg]  t3=%.4f [seg] \n', t1, t2, t3 );
return;
