%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Comunicações.
%
% pol_div.m
% Função que calcula o resto da divisão entre dois polinomios
% de coeficientes binários.
%
% Recebe:
% A  - Coeficientes do polinómio numerador.
% B  - Coeficientes do polinómio denominador.
%
% Retorna:
% R  - Resto da Divisão entre A e B.
%
function R = pol_div(A ,B)

mx = A;
nc = 0;
while (nc <= length(mx))

    nc = nc + 1;

    % Quando encontra o 1 faz a divisao.
    if mx(nc) == 1
        mx(nc:nc+length(B)-1) = xor(mx(nc:nc+length(B)-1),B);
    end

    % Quando percorre ate ao fim de M(x)*2^n sai do ciclo
    if (nc+length(B)-1) >= length(mx)
        break;
    end
end

% Obter o resto da divisão.
R  = [ mx(length(mx)-length(B)+2:length(mx)) ];
end