function [Signal,FS]= emissor(signal,Fo,Mod)
    
    if (strcmpi(Mod,'OOK'))
        %Modelação OOK
        [Signal,FS]=OOK(signal,5,0,Fo);
    elseif(strcmpi(Mod,'PSK'))
        %Modelação PSK
        [Signal,FS]=PSK(signal,5,-5,Fo);
    else
        fprintf('Modulação indicada é ínválida.\n');
        return;
    end
end