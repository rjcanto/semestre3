function  [out , TSinal] = ex1aDAC( sinal , TSinal)
%******************
%execicio 3 a)
%******************
%sinal = [0,0 , 0 , 1 , 1 ,0 , 1 ,1];
%TSinal = 0.001;

FS = 20000;
limit = (length(sinal)/2);

t = 0 : 1/FS : limit*TSinal;
idx = 1;
par = 1;
isZero = 0;
phaseShift = zeros([1 limit]);


%DAC - Array de bits para tensões

while(idx <= length(sinal))
    if(par == 0)
    switch sinal(idx)
        case 0 
            if(isZero == 0)    
                phaseShift(idx/2) = pi/4;
                par = 1;
            end
            if(isZero == 1)
                phaseShift(idx/2) = (7*pi)/4;
                par = 1;
            end
        case 1
            if(isZero == 0)    
                phaseShift(idx/2) = (3*pi)/4;
                par = 1;
            end
            if(isZero == 1)
                phaseShift(idx/2) = (5*pi)/4;
                par = 1;
            end
    end
    else
        isZero = sinal(idx);
        par = 0;
    end
    idx = idx +1;
end

tout = getpulse(phaseShift(1) , FS , TSinal);

%Função de envio de Sinal
for idx = 2 : limit    
    tout = horzcat(tout , getpulse(phaseShift(idx) , FS , TSinal));
end
out = zeros([1 , length(t)]);

for idx=1 : length(out)
    out(idx) = tout(idx);
end

plot(t , out);
title('Sinal Saída');
xlabel(' Tempo ');
ylabel(' Amplitude ');
grid on;

function [pulse] = getpulse(phase , FS , TSinal)

tx = 0 : 1/FS : TSinal;
pulse = 3*cos(2*pi*2000*tx + phase);


