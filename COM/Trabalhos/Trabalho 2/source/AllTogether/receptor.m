function [signal] = receptor(signal,FS,TB,modulationType)
    %signal=signal.*filtroPassaBaixo(length(FS));
	%signal=ifft(signal);
    signal=correlador(signal,FS,TB,modulationType);
end