function [erros] = teste(Signal, Mod, Type,Fc, SNR, num)

erros=0;
result = zeros(1,length(Signal));

for i=1:num 
    result=main(Signal,10000,Mod,Type,Fc, SNR);
    if(~isequal(Signal,result)) 
        erros=erros+1;
    end
end
end

