%
% ISEL - Instituto Superior de Engenharia de Lisboa.
%
% LEIC - Licenciatura em Engenharia Informatica e de Computadores.
%
% Com  - Comunicações.

function exemplo_imagens()

close all;

% 1)Grayscale
% Ler a imagem.
%filename = 'trees.tif';
%filename = 'cameraman.tif';
filename = 'circuit.tif';
I = imread( filename );
% Mostrar imagem
figure; imshow(I); 
title( 'Imagem Original ');

% Obter as dimensões da imagem.
[NRows, NCols] = size(I);



%-----------------------------------------------------------------------
% 2) Imagem a cores.
% Conversao para grayscale
filename = '136.jpg';
I = imread( filename );
figure; imshow(I); title( 'Imagem Original RGB');
gray = 0.2989 * I(:,:,1) + 0.5870 * I(:,:,2) + 0.1140 * I(:,:,3); 
figure; subplot(2,2,1); imshow(gray); 
title( 'Imagem Original Grayscale');
%http://en.wikipedia.org/wiki/YUV
%RGB2YUV=[0.299	0.587	0.114;
%-0.14713 -0.28886 0.436;
%0.615 -0.51499 -0.10001];
%[Y;U;V]=RGB2YUV*[R;G;B]; 


% 3) Somar ruído para ver efeito... 
J = imnoise(gray,'salt & pepper',0.02);
%http://www.mathworks.com/access/helpdesk/help/toolbox/images/index.html?/access/helpdesk/help/toolbox/images/imnoise.html
subplot(2,2,2); imshow(J); 
title( 'Imagem Grayscale com ruído ');


% 4) operacoes sobre imagens
h = fspecial('average',3);
%http://www.mathworks.com/access/helpdesk/help/toolbox/images/index.html?/access/helpdesk/help/toolbox/images/fspecial.html
filtered1 = imfilter(J,h);
subplot(2,2,3); imshow(filtered1); 
title( 'Imagem Grayscale com ruído após filtro de média');

K = medfilt2(J);    %2-D median filtering
subplot(2,2,4); imshow(K);
title( 'Imagem Grayscale com ruído após filtro de mediana');


%--------------------------------------------------------------------------
% 5 ) Exemplo da operação de deblur

I = imread('peppers.png'); 
I = I(10+[1:256],222+[1:256],:); 
figure;
subplot(1,3,1);
imshow(I);title('Original Image');

LEN = 31;
THETA = 11;
PSF = fspecial('motion',LEN,THETA);
Blurred = imfilter(I,PSF,'circular','conv');
subplot(1,3,2);
imshow(Blurred);title('Blurred Image');

wnr1 = deconvwnr(Blurred,PSF);
subplot(1,3,3); imshow(wnr1);
title('Restored, True PSF');



