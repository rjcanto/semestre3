%Exercicio 1.b.
%Efectue testes que permitam aferir a sensibilidade do sistema auditivo humano à variação na amplitude,
%frequência e fase da sinusóide. Escolha um valor adequado para a frequência de amostragem Fs. Apresente
%os resultados desses testes e comente-os.
%http://www.audicaocritica.com.br/o-que-e/211-equalizador-de-fase-linear.ht
%ml
%Input:
%Output:
function [] = t1b_testes()
    %Amplitude:
    %variação de amplitude faz variar o volume do sinal audivel. maior
    %amplitude, som mais alto, menor amplitude som mais baixo.
    %Frequencia:
    %Quanto maior a frequencia mais rápido o som  se torna mais agudo, quanto menor, mais
    %lento, som mais grave.
    %Fase:
    %Não foi notada diferença
    A_test=2;
    frq_test=440;
    sec=0.5;
    ph=0;
    %Teste de Amplitude
    fprintf('Teste de Amplitude.\n');
    for A=1:5
        t1_nota(A,frq_test,sec,ph);
    end
    pause(2);

    %Teste de Frequencia
    fprintf ('##########################################\n');
    fprintf (' Teste ao nivel de frequencia mínima audivel.\n');
    fprintf ('##########################################\n');
    fprintf('Frequencia: ');
    for frq_test=1:30
        fprintf(' %i ',frq_test);
        [s,fs]=t1_nota(A_test,frq_test,sec,ph);
        sound(s,fs);
    end
    fprintf('\n');
    
    fprintf ('##########################################\n');
    fprintf (' Teste ao nivel de frequencia máxima audivel.\n');
    fprintf ('##########################################\n');
    fprintf('Frequencia: ');
    for frq_test=1:30
        x=19000 + 1000*frq_test;
        [s,fs]=t1_nota(A_test,x,sec,ph);
        fprintf(' [%i <-> %i] ',x,fs);
        sound(s,FS);
    end
     fprintf('\n');
    

    fprintf('Teste de Fase.\n');
    %Teste de Fase
    frq_test=263.61;
    for ph=0:pi/12:2*pi
      t1_nota(A_test,frq_test,sec,ph);  
    end
end
