%
%Precisa de ser corrigido
%

function [result] = decisor(Signal,Tb,Modulation)
    if (strcmpi(Modulation,'OOK'))
		Eb=5*5*Tb/2;
            if (Signal > Eb/2)
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