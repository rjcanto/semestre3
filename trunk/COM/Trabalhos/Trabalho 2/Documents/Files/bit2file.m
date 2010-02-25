%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% bit2file.m
%
%
% Recebe:   bistream, vector no qual cada posição é um bit.
%           filename, nome do ficheiro destino.
% Retorna:  x, ficheiro na forma de vector
%
function  x = bit2file( bitstream, filename )

% Criar o vector com elementos do tipo inteiro a 8 bit.
x = uint8( zeros(1, length(bitstream) / 8 ) );

% Vector com as potencias de 2.
p2 = 2.^(7:-1:0);

% Calcular ponto a ponto.
k = 1;
for i=1: length(x)
    x(i) = bitstream( k:k+7 ) * p2';
    k = k + 8;
end

% Passar para ficheiro.
vector2file(x, filename);
return;



%
%
%
function vector2file(x, filename)

% Open file.
fid = fopen( filename, 'wb' );

% Check descriptor.
if -1==fid
    error( sprintf('Error opening file %s for writing ',filename) );
end

% Write the vector.
fwrite( fid, x, 'uchar' );

% Close file.
fclose( fid );

return;

