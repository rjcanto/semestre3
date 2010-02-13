%
%Precisa de ser corrigido
%

function [result] = decisor(Signal,Tb,Modulation)
    Eb=Signal*Signal*Tb;

    if (strcmpi(Modulation,'OOK'))
            if (Signal/2 > Eb)
                result = 1;
            else
                result =0;
            end
    elseif(strcmpi(Modulation,'PSK'))
            if (Signal > Eb)
                result = 1;
            else
                result =0;
            end
    else
        fprintf('Modulação indicada é ínválida.\n');
        result=-1;
        return;
    end
    
end