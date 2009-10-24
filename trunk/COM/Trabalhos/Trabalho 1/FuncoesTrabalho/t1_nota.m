%Geração de Nota Musical.
%
%Input:
%   a=  Amplitude
%   fs= Frequencia de Amostragem
%   ph= Fase
%
%Output:
%   nota: retorna a respectiva nota.
%   fs: retorna a frequencia de amostragem
%
function [nota,fs] = t1_nota(a,fi,sec,ph)
    %Help Source:
    %http://www.members.tripod.com/caraipora/esc_temp_freq_.htm
    if (nargin ~= 4)
        if (nargin == 3)
            ph=0;
        else    
            fprintf('Numero de argumentos inválido.\n');
            help t1_notas;
            return;
        end
    end


    %numero de segundos de cada nota.
    %sec=1;
    %Frequencia de Amostragem (em Hz), taxa equivalente do sinal de telefone
    fs=4096;
    %frequencia base de 261.63 hz, é a frequencia padrão da nota Dó num piano.
    %
    
    n=1:1:fs*sec;
    W=2*pi*(fi/fs);
    %sinal a ser gerado
    if (fi == 0)
        nota=zeros(1, round((fs*sec)/100));
    else
        nota=a*cos(W * n  + ph);
    end
    %wavplay(nota,fs);
end
