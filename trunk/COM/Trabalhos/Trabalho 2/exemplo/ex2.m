% Recebe:
% mensagem = mensagem a enviar
% ex = 0 se erro aleatórios 1 se erros em burst
% sizeburst = número de bits errados em modo burst
% graph = 0 se não pretende gráfico 1 se pretende gráfico

function ex2 (mensagem , ex , sizeburst, graph)
    error = [0 0 0];
    time = 0;
    while(time < 10000)
    time = time + 1;
    g1 = [1 0 1 1]; catG1 = [0 0 0];
    g2 = [1 1 0 1 0 0 0 1]; catG2 = [0 0 0 0 0 0 0];
    g3 = [1 1 0 0 0 0 0 0 0 1 1 1 1]; catG3 = [0 0 0 0 0 0 0 0 0 0 0 0];
    
    mensagemG1 = horzcat( mensagem , catG1);
    mensagemG2 = horzcat( mensagem , catG2);
    mensagemG3 = horzcat( mensagem , catG3);
    
      %commentar se utilizar pol_div
%     [menG1 resG1] = deconv( mensagemG1 , g1);
%     [menG2 resG2] = deconv( mensagemG2 , g2);
%     [menG3 resG3] = deconv( mensagemG3 , g3);
      %---------------------------------------
    
    %commentar se utilizar deconv  
    resG1 = pol_div(mensagemG1 , g1);
    resG2 = pol_div(mensagemG2 , g2);
    resG3 = pol_div(mensagemG3 , g3);
    %---------------------------------------
        
      %commentar se utilizar pol_div  
%     mensagemG1 = mensagemG1 | mod(resG1 , 2);
%     mensagemG2 = mensagemG2 | mod(resG2 , 2);
%     mensagemG3 = mensagemG3 | mod(resG3 , 2);
      %---------------------------------------
    
    %commentar se utilizar deconv    
    mensagemG1 = horzcat(mensagemG1, resG1);
    mensagemG2 = horzcat(mensagemG2, resG2);
    mensagemG3 = horzcat(mensagemG3, resG3);
    %---------------------------------------
  
    if(ex < 2) 
        ErrorG1 = ex2b(mensagemG1 , ex , sizeburst);
        ErrorG2 = ex2b(mensagemG2 , ex , sizeburst);
        ErrorG3 = ex2b(mensagemG3 , ex , sizeburst);
    else
        fprintf('Desconhecido'); 
    end
    
    %commentar se utilizar pol_div 
    %[menG1 resG1] = deconv( ErrorG1 , g1);
    %[menG2 resG2] = deconv( ErrorG2 , g2);
    %[menG3 resG3] = deconv( ErrorG3 , g3);
    %---------------------------------------
    
    resG1 = pol_div(ErrorG1 , g1);
    resG2 = pol_div(ErrorG2 , g2);
    resG3 = pol_div(ErrorG3 , g3);
    
    
    %commentar se utilizar pol_div
    %if(sum(mod(resG1 , 2)) == 0)
    %---------------------------------------
    
    %commentar se utilizar deconv
    if(sum(resG1) == 0)
    %---------------------------------------
    
        if(graph == 0)
            fprintf ('Não Existe Erros com G1\n')
        end
        error(1) = error(1) + 1;
    else
        if(graph == 0)
            fprintf ('Existe Erro com G1\n')
        end
    end
    
    %commentar se utilizar pol_div
    %if(sum(mod(resG2 , 2)) == 0)
    %---------------------------------------
    
    %commentar se utilizar deconv
    if(sum(resG2) == 0)
    %---------------------------------------
    
        if(graph == 0)
            fprintf ('Não Existe Erros com G2\n')
        end
        error(2) = error(2) + 1;
    else
        if(graph == 0)
            fprintf ('Existe Erro com G1\n')
        end
    end
    
    %commentar se utilizar pol_div
    %if(sum(mod(resG3 , 2)) == 0)
    %---------------------------------------
    
    %commentar se utilizar deconv
    if(sum(resG3) == 0)
    %---------------------------------------
    
        if(graph == 0)
            fprintf ('Não Existe Erros com G2\n')
            break;
        end
        error(3) = error(3) + 1;
    else
        if(graph == 0)
            fprintf ('Existe Erro com G3\n')
        end
    end
    
    end
    if(graph == 1)
        bar(error);
        title(['Não foi detectado erro em G1: ' num2str(error(1)),' X.',' Não foi detectado erro em G2: ' num2str(error(2)),' X.',' Não foi detectado erro em G3: ' num2str(error(3)),' X. Em ' num2str(time), ' Tentativas']);
        xlabel(' 1(G1)         2(G2)         3(G3) ');
        ylabel(' Nº de vezes que não foi detectado erro. ');
    end
    
     
    