function [signal] = receptor(signal,FS,TB,modulationType)
    
    signal=correlador(signal,TB,FS,modulationType);
    HammingDecoding(signal);



end