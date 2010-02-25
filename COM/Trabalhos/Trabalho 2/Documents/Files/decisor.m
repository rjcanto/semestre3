function [result] = decisor(Signal,Modulation)
    [TB,Amp]=NRZValues();
    if (strcmpi(Modulation,'OOK'))
		Eb=Amp*Amp/2;
            if (Signal > Eb/2)
                result = 1;
            else
                result =0;
            end
    elseif(strcmpi(Modulation,'PSK'))
		    if (Signal > 0)
                result = 1;
            else
                result = 0;
            end
    else
        fprintf('Modulação indicada é ínválida.\n');
        result=-1;
        return;
    end
end