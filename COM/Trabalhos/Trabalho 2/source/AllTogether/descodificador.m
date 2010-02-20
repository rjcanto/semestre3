function [sinal_out] = descodificador(sinal)
%Função que recebe um sinal digital codificado na forma de 
%[4 bits mensagem + 7 bits paridade] e verifica se existiram
%erros de transmissão. Detecta até 4 bits em erro e corrige 2


%nº de bits de mensagem
numBits=4;

%Sub-matriz Geradora Paridade P
P=[[1,1,0,1,0,0,1]
   [1,1,1,0,1,1,0]
   [1,0,1,1,0,1,0]
   [0,1,1,1,1,0,1]];
            
%Matriz Controlo Paridade H
%H' é a matriz com os sindromas de erro de 1 bit (11 possibilidades)
H = horzcat(P',eye(7));

%Agora é necessário construir a matriz dos sindromas para erros de 2 bit
%Sera uma matriz com 55 sindromas (Combinações de 11, 2 a 2)
    k=1;
    for i=1:10
        for j=i+1:11
            m_sindromas(k,i)=1;
            m_sindromas(k,j)=1;
            k=k+1;
        end;
    end;

%Matriz com os bits a corrigir para cada sindroma
corrigeBits = vertcat(zeros(1,11),eye(11),m_sindromas);
%corrigeBits
m_sindromas=0;
%Matriz com todos os sindromas de 2 bits
%calculada multiplicando a matrix de correcção com a Matriz Controlo Paridade transposta 
    for i=1:length(corrigeBits)
        m_sindromas(i,1:7)= mod((corrigeBits(i,1:11)*H'),2);
    end;
    %m_sindromas

%Processamento do sinal de entrada
%Por cada bloco de 11 bits, verifica se existe erro e se sim, corrige o
%mesmo construindo o sinal final usando apenas os 4 bits de mensagem

sinal_out=zeros(1,length(sinal)/11*4);
    for x=1:11:length(sinal)
        %variavel que permite saber se foi detectado erro fora dos limites
        %de correcção - mais do que dois bits em erro
        sinal_p=0;
        sindroma = mod(sinal(1,x:x+10)*H',2);
        for i=1:length(m_sindromas)
            if (sindroma == m_sindromas(i,1:7))
                sinal_out(1,(floor(x/11)*4+1):(floor(x/11)*4+1)+3) = (mod(sinal(1,x:x+3) + corrigeBits(i,1:4),2));
                sinal_p = 1;
                break;
            end;   
        end;
        if(sinal_p==0)
            %se sinal tem mais do que 3 bits em erro então mantem sinal da
            %entrada na saída e informa utilizador
            sinal_out(1,((x-1)/11*4+1):((x-1)/11*4+1)+3) = sinal(1,x:x+3);
%             fprintf('!!!Erro de transmissão!!!\n');
%             fprintf('Mais de dois bits trocados entre o bit %d e o bit %d.\n',x, x+10);
%             fprintf('Transmissão deverá ser repetida.');
        end;
    end;
%sinal_out
end
