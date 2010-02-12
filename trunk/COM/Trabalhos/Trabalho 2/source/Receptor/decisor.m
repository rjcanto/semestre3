%
%Precisa de ser corrigido
%

function [result] = decisor(Signal,A,Tb,Modulation)
    test=A*A*Tb/2;
    
    if (strcmpi(Modulation,'OOK'))
            if (Signal>test)
                result = 1;
            else
                result =0;
            end
    elseif(strcmpi(Modulation,'PSK'))
            if (Signal > 0)
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