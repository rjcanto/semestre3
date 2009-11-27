function [yT,fs]= emissor()
clear all;
fo=100;
fo2=20;
fs=2.2*fo;
t=0:1/(fs-1):1;

aT=cos(2*pi*fo*t);
xT=(1+cos(2*pi*fo2*t));
x2T=sinc(t);
figure ;
my_analysis(xT,fs);

yT=xT.*aT;
y2T=x2T.*aT;
figure ;
my_analysis(yT,fs);
figure;
my_analysis(y2T,fs);
end