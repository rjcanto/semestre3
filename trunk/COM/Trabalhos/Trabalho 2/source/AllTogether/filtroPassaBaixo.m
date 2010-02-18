% Cria um vector que serve como filtro passa baixo como frequencia de corte
% fs.

function [Filtro] = filtroPassaBaixo(fs)
    Filtro=1:2*fs;
    leftLimit=floor(fs/2);
    rightLimit=fs + floor(fs/2);
    for i=1:fs
        if (i<=leftLimit || i>rightLimit )
            Filtro(i)=0;
        else
            Filtro(i)=1;
        end
    end
end
