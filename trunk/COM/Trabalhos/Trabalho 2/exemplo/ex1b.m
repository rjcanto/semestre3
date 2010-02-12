function ex1b(sinal , TSinal)
%******************
%execicio 3 b)
%******************
    BE = 0;
    out = ex1bDAC(sinal , TSinal);
    limit = sum(out.^2);
    SNR = 1 : 100 : limit;
    BER = 1 : 100 : limit;
    for idx = 1 : length(SNR)
        NoisySinal = ex1aNOISE(SNR(idx) , out);
        outSinal = ex1bADC(NoisySinal , TSinal);
        for idx1 = 1 : length(outSinal)
            if(sinal(idx1) ~= outSinal(idx1))
                BE = BE + 1;
            end
        end
    BER(idx) = BE;
    BE = 0;
    end
    figure;
    plot (SNR , BER);
    grid on;
    title('Curva BER');
    ylabel ('Erros em bit na trama');
    xlabel ('SNR');
    print( gcf, '-djpeg100', 'SinalCDE.jpg' );