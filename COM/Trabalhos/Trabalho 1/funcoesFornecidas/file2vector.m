%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% file2vector.m
% Funçao que lê o conteúdo de um ficheiro e o coloca num vector.
%
% Recebe:		filename    - nome do ficheiro.
% Retorna:      y           - vector com o conteudo do ficheiro.             

function y = file2vector( filename )

% Open file.
fid = fopen( filename, 'rb' );

% Check descriptor.
if -1==fid
    error( sprintf('Error opening file %s for reading',filename) );
end

% Read entire file to a vector.
y = fread( fid, Inf, 'uchar' );

% Line vector.
y = y';

% Close file.
fclose( fid );

return;


