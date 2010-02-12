%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.
%
% converteBits.m
% Teste das funções file2bit  e bit2file.
% Teste das funções image2bit e bit2image.
%  
%
% pode usar as funcionalidades de execução das cells definidas para
% executar os vários blocos de código. 
% Nota: para isso deve abrir este script a partir do matlab

%%
%--------------------------------------------------------
% Teste das  funções file2bit  e bit2file.
%--------------------------------------------------------
% 
% Teste 1.
%
fprintf('file2bit e bit2file - teste 1\n')
b = file2bit( 'c:\\a.txt' );
x = bit2file( b, 'c:\\b.txt' );

% Comparar os vectores.
% Deve dar zero.
sum( double(x) - file2vector('c:\\a.txt') )
% Chamar o editor do MATLAB.
edit('c:\\b.txt')

%%
% 
% Teste 2.
%
fprintf('file2bit e bit2file - teste 2\n')
b = file2bit( 'fig1.gif' );
x = bit2file( b, 'fig1a.jpg' );

% Comparar os vectores.
% Deve dar zero.
sum( double(x) - file2vector('fig1.gif') )



%%
%--------------------------------------------------------
% Teste das funções image2bit e bit2image.
%--------------------------------------------------------

% 
% Teste 1 - com matriz simples.
%
fprintf('image2bit e bit2image - teste 1\n')
% Estabelecer a matriz de teste.
A  = [1 2; 7 8]

% Converter para o vector de bits. 
b  = image2bit( A )

% Converter de vector de bits para matriz.
% size(A,1) é o número de linhas de A.
% size(A,2) é o número de colunas de A.
A2 = bit2image( size(A,1), size(A,2), b)

% Comparar as matrizes.
% Deve dar zero.
sum(sum( double(A) - double(A2) ))


%%
%
% Teste 2 - com imagem em niveis de cinzento.
% Imagens a cores não são suportadas. 
% Devem ser convertidas em grayscale...
%
fprintf('image2bit e bit2image - teste 2\n')
% Ler a imagem.
filename = 'trees.tif';
%filename = 'cameraman.tif';
%filename = 'circuit.tif';
I = imread( filename );

% Obter as dimensões da imagem.
[NRows, NCols] = size(I);

% Converter para vector e de vector para matriz.
b  = image2bit( I );
I2 = bit2image(NRows, NCols, b);

% Mostrar as imagens.
figure;
subplot(1,2,1); imshow(I);
subplot(1,2,2); imshow( uint8(I2) );

% Comparar as imagens pixel a pixel.
% Deve dar zero.
sum(sum( double(I) - double(I2) ))