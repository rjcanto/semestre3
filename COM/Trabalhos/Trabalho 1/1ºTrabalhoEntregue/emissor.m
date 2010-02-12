function [yF,FS]= emissor(signal,Fo)
    %wavplay(signal,Fo);
    carrierFS=10000;
    FS=2.2*(carrierFS+Fo);
    t=0:1:length(signal)-1;

   figure('name','Sinal Original');
   my_analysis(signal,Fo); 


    %Sinal da Portadora
    aT=cos(((2*pi*carrierFS)/FS)*t)';
    yT=aT.*signal;
    figure('name','Sinal yT à Saida do Emissor');
    my_analysis(yT,FS); 

    yF=fft(yT);
end