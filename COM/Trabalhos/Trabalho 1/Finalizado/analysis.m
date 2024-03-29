%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunica��es.
%
% analysis.m
% An�lise de sinal contido em ficheiro wave ou vector dado como parametro.
% Recebe:
%      filenameOrVector, nome do ficheiro wave ou vector com as amostras do sinal.
%      gravaImagem ( 0 ou 1) 
% Retorna:
%      um vector com sinal contido no ficheiro / ou vector passado por
%      parametro
function x = analysis( filenameOrVector , gravaImagem)

% Testar se e' string (nome de ficheiro) ou vector.
if isstr(filenameOrVector)
    
    filename = filenameOrVector;
    
    % E' uma string. Ler o ficheiro.
    [x, Fs, n] = wavread( filename );    
    
    % Mostrar par�metros do sinal.
    fprintf('Ficheiro. Sinal com %.3f segundos  Fs=%d Hz  n=%d bit/amostra \n', length(x)/Fs, Fs, n );
else
    % E' um vector.
    x = filenameOrVector;
    
    % Assumir os valores de Fs e n.
    Fs = 8000;
    n = 8;
    fprintf('Vector. Assume-se Fs=%d e n=%d bit/amostra \n', Fs, n );    
    filename = 'Vector';
end


% Calibrar o eixo dos tempos em segundos.
time = (0 : 1 : length(x)-1) / Fs;

% Calibrar o eixo das frequ�ncias em Hertz.
freq = ((0 : 1 : length(x)-1)*Fs / ( length(x) )) - Fs/2;

% Mostrar o sinal no tempo e o seu espectro. 
% Tempo.
subplot(3,1,1); 
plot( time, x ); 
grid on; title(filename); 
xlabel('Tempo [seg]'); ylabel('Amplitude');

% Espectro.
subplot(3,1,2); 
plot( freq, fftshift(abs(fft(x))) ); 
grid on; title('Espectro (m�dulo) '); 
xlabel('Frequencia [Hz]'); ylabel('M�dulo');

% Espectrograma.
subplot(3,1,3); 
specgram( x , 256, Fs); 
grid on; title('Espectrograma'); 
xlabel('Tempo [seg]'); ylabel('Frequencia [Hz]');

if (gravaImagem==1)
    % Escrever a figura num ficheiro JPEG.
    print( gcf, '-djpeg100', strcat(strtok( filename, '.'),'.jpg') );
end

return;
        