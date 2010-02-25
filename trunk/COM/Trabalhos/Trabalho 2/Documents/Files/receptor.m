function [signal] = receptor(signal,FS,modulationType)
    %signal=signal.*filtroPassaBaixo(length(FS));
	%signal=ifft(signal);
    signal=correlador(signal,FS,modulationType);
end