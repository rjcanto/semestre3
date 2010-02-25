%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% analysis.m
% Análise de sinal contido em ficheiro wave ou vector dado como parametro.
% Recebe:
%      filenameOrVector, nome do ficheiro wave ou vector com as amostras do sinal.
%      gravaImagem ( 0 ou 1) 
% Retorna:
%      um vector com sinal contido no ficheiro / ou vector passado por
%      parametro
function x = analysis( filenameOrVector , Fs)

% Testar se e' string (nome de ficheiro) ou vector.
if ischar(filenameOrVector)
    
    filename = filenameOrVector;
    
    % E' uma string. Ler o ficheiro.
    [x, Fs, n] = wavread( filename );    
    
    % Mostrar parâmetros do sinal.
    fprintf('Ficheiro. Sinal com %.3f segundos  Fs=%d Hz  n=%d bit/amostra \n', length(x)/Fs, Fs, n );
else
    % E' um vector.
    x = filenameOrVector;
    
    % Assumir os valores de Fs e n.
    %Fs = 8000;
    fprintf('Vector. Assume-se Fs=%d \n', Fs );    
    filename = 'Vector';
end


% Calibrar o eixo dos tempos em segundos.
time = (0 : 1 : length(x)-1) / Fs;

% Calibrar o eixo das frequências em Hertz.
freq = ((0 : 1 : length(x)-1)*Fs / ( length(x) )) - Fs/2;

% Mostrar o sinal no tempo e o seu espectro. 
% Tempo.
subplot(3,1,1); 
plot( time, x ); 
grid on; title(filename); 
xlabel('Tempo [seg]'); ylabel('Amplitude');

% Espectro.
subplot(3,1,2); 
fftshift(abs(fft(x)))
plot( freq, fftshift(abs(fft(x))) ); 
grid on; title('Espectro (módulo) '); 
xlabel('Frequencia [Hz]'); ylabel('Módulo');

% Espectrograma.
subplot(3,1,3); 
specgram( x , 256, Fs); 
grid on; title('Espectrograma'); 
xlabel('Tempo [seg]'); ylabel('Frequencia [Hz]');
return;
        