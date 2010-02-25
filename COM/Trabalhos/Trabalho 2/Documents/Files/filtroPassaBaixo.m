% Cria um vector que serve como filtro passa baixo como frequencia de corte
% fs.

function [Filtro] = filtroPassaBaixo(fs,fc)

    Filtro=fs;
    for i=1:length(Filtro)
        if (abs(Filtro(i))>fc)
            Filtro(i)=0;
        else
            Filtro(i)=1;
        end
    end
end
