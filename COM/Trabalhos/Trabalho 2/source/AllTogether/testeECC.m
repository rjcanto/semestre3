function [erros] = testeECC()

InSignal=[1 0 1 1];


    CodedSignal = geraCodigo(InSignal)
     CodedSignal(8)= mod(CodedSignal(8)+1,2)
      CodedSignal(6)= mod(CodedSignal(6)+1,2)
     CodedSignal(7)= mod(CodedSignal(7)+1,2)
%     CodedSignal(8)= mod(CodedSignal(8)+1,2)
%     CodedSignal(12)= mod(CodedSignal(12)+1,2)
%     CodedSignal(17)= mod(CodedSignal(17)+1,2)

    [signal,FS]=emissor(CodedSignal,10000,'ook');    
    OutSignal=receptor(signal,FS,'ook');
    OutSignal=descodificador(OutSignal);
   
    OutSignal
end