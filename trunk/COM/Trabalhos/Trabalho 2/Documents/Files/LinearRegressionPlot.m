function [] = LinearRegressionPlot(xSNR,BER,Message)
    figure;
    [p,ErrorEst] = polyfit(xSNR,BER,2);
     % Evaluate the fit
    pop_fit = polyval(p,xSNR,ErrorEst);
    % Plot the data and the fit
    plot(xSNR,pop_fit,'-');
    title(Message);
    xlabel('SNR (Unidades Lineares)');
    ylabel('BER');
end

