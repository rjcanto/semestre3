function [signal] = receptor(signal,FS,TB,modulationType)
    %signal=ifft(signal);

    %signal=signal.*filtroPassaBaixo(length(TB));

    signal=correlador(signal,FS,TB,modulationType);




end