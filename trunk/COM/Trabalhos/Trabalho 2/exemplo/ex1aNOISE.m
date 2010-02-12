function [NoisySinal] = ex1aNOISE (SNR , sinal)
    %******************
    %execicio 3 b)
    %******************
    Es = sum(sinal.^2);
    r = rand(size(sinal));
    
    %snr = (AmplitudeSinal/AmplitudeRuido)^2 => sqrt(snr)*Ar = As 
    
    Er = Es/SNR;
    
    Vr = r * Er;
    
    NoisySinal = sinal + Vr;
    
    %t = 0 : 1/20000 : (1+4)*1; 
  
end
    