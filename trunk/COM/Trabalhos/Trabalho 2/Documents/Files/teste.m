function [erros] = teste(Signal, Mod, Type,Fc, num)

erros=0;
result = zeros(1,length(Signal));

for i=1:num 
    result=main(Signal,10000,Mod,Type,Fc);
    if(result~=Signal) 
        erros=erros+1;
    end
end
end

