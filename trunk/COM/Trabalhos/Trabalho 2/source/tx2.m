% Modifique a função anterior de forma a que, para além da adição de 
% ruído, o canal de transmissão realize também filtragem do tipo 
% passa-baixo com frequência de corte programável (função tx2)

function [Y]=tx2(signal,SNR,fs)
    signal_F=fftshift(fft(signal));

    Filtro=filtroPassaBaixo(fs);
    signal=ifft(signal_F.*Filtro);
Y=tx1(signal,SNR);
end