function []=t1_notas()
    %Twinkle=[1 0.5 1 0.5 5 0.5 5 0.5 6 0.5 6 0.5 5 1 4 0.5 4 0.5 3 0.5 3 0.5 2
    %0.5 2 0.5 1 1 5 0.5 5 0.5 4 0.5 4 0.5 3 0.5 3 0.5 2 1 5 0.5  5 0.5 4 0.5 
    %4 0.5 3 0.5 2 1 1 0.5 1 0.5 5 0.5 5 0.5 6 0.5 6 0.5 5 1 4 0.5 4 0.5 3 0.5 3 0.5 2 0.5 2 0.5 1 1]
    %
    
    %Jingle=[3 0.5 3  0.5 3  1 0  0.5 3  0.5 3  0.5 3  1 0  0.5 3  0.5 5
    %0.5 1  0.5 2  0.5 3  1 0  0.5 0  0.5 0  0.5 4  0.5 4  0.5 4  0.5 4
    %0.5 4  0.5 3  0.5 3  0.5 3  0.5 3  0.5 2  0.5 2  0.5 3  0.5 2  0.5 0  
    %0.5 5  0.5 0  0.5 3  0.5 3  0.5 3  0.5 0  0.5 3  0.5 3  0.5 3  0.5 0  
    %0.5 3  0.5 5  0.5 1  0.5 2  0.5 3  0.5 0  0.5 0  0.5 0  0.5 4  0.5 4  
    %0.5 4  0.5 4  0.5 4  0.5 3  0.5 3  0.5 3  0.5 5  0.5 5  0.5 4  0.5 2  0.5 1  0.5 0  0.5 0  0.5 0 0.5]
    %
    %
    amplitude=2;
    frq=261.63;
    phase=3/4*pi;
    t1_nota(amplitude,frq*power(2,1/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,1/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,6/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,6/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),1,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,1/12),1,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),1,phase);
    t1_nota(amplitude,frq*power(2,1/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,1/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,6/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,6/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,5/12),1,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,4/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,3/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,2/12),0.5,phase);
    t1_nota(amplitude,frq*power(2,1/12),0.5,phase);
    
    
% 
%     for i=0:n
%         notas=t1_nota(amplitude,frq,0.5,phase);
%         frq=frq*power(2,1/12);
%     end
end
