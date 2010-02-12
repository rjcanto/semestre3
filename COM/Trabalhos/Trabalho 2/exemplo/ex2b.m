function [mensagemComErro] = ex2b(mensagem , tipo , sizeBurst)

mensagemComErro = zeros([1 length(mensagem)]);
burststartpoint = rand(1,1) * 3;

if( tipo == 0)
    mensagemComErro(1) = ~mensagem(1); %certifica-se que existe sempre pelo menos um bit errado
    for idx = 2 : length(mensagem)
        mensagemComErro(idx) = randint;
    end
else
if( tipo == 1)
    for idx = 1 : length(mensagem)
        if (idx <= sizeBurst)
            switch burststartpoint
                case 1 
                    mensagemComErro(idx) = ~mensagem(idx);
                case 2 
                    mensagemComErro((length(mensagem)/2)+idx) = ~mensagem((length(mensagem)/2)+idx);
                case 3
                    mensagemComErro(sizeBurst-length(mensagem)+idx) = ~mensagem(sizeBurst-length(mensagem)+idx);
            end
        else
            mensagemComErro(idx) = mensagem(idx);
        end
    end
else
    fprintf('Desconhecido');
end
end
