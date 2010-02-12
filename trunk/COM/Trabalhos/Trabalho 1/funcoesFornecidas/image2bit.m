%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% image2bit.m
%
% Recebe:   I, matriz com valores inteiros (uint8).
% Retorna:  b, vector com os bits que compoem os elementos da matriz.
%              Este vector é do tipo double (sem optimização!).
%
function  b = image2bit( I )

   [NRows, NCols, NBands] = size(I);
   if 1~=NBands
     fprintf(' Imagem com %d bandas \n', NBands );  
     error( 'Apenas se suportam imagens em níveis de cinzento ' );
   end   
   
   b = double(reshape( blkproc( I, [1 1], @bitget, 8:-1:1 )',...
        [1 size(I,1)*size(I,2)*8] ));
return;