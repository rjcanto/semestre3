function [yT,fs]= emissor()
fo=10000;
fo2=2000
fs=2.1*fo;

t=0:1/fs:1;

aT=cos(2*pi*fo*t);

xT=1 + cos(2*pi*fo2*t);
x2T=sinc(t);
yT=aT.*xT;
y2T=x2T.*aT;
%figure;
%stem(aT);
%title("aT");
%figure;
%stem(xT);
%title("xT");
%figure;
%stem(yT);
%title("yT");
%figure;
%plot(t2,xT);
%title("x2T");
%figure;
%plot(t2,yT);
%title("y2T");

end