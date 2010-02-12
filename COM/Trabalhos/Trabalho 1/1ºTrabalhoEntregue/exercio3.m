function [newXT,TS]= exercicio3(nbr)

    fo=10000;
  
    fs=2.2*fo;
    t=0:1/(fs-1):1;

    switch nbr
        case 1
            fo2=2000;
            xT=(1+cos(2*pi*fo2*t))';  
        case 2
            fo2=2000;
            xT=(sinc(t))';
        case 3
            [xT,fo2]=wavread('fala4.wav');
        otherwise
            return;
    end
    %
    %Fase de Emissor
    %
    
    [yF,FS]=emissor(xT,fo2);
    
    %
    %Fase de Receptor
    %
    [newXT,TS]= receptor(yF,FS);
end