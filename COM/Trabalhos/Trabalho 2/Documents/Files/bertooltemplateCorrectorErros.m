function [ber, numBits] = bertooltemplateCorrectorErros(EbNo, maxNumErrs, maxNumBits)
% Import Java class for BERTool.
import com.mathworks.toolbox.comm.BERTool;

% Initialize variables related to exit criteria.
totErr = 0;  % Number of errors observed
numBits = 0; % Number of bits processed

% --- Set up parameters. ---
    Fo=10000;
    Fc=8000;
    InSignal=[1 0 1 1 1 0 0 0 1 0 1 0 1 0 1 0 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0];
    sigLen = length(InSignal);
    ntrials=0;
    
    t=1;
    Mod='psk';
    
% Simulate until number of errors exceeds maxNumErrs
% or number of bits processed exceeds maxNumBits.
while((totErr < maxNumErrs) && (numBits < maxNumBits))

   % Check if the user clicked the Stop button of BERTool.
   if (BERTool.getSimulationStop)
      break;
   end

   % --- Proceed with simulation.
   % --- Be sure to update totErr and numBits.
    OutSignal=main(InSignal,Fo,Mod,t,Fc,EbNo);
    newerrs=BER(InSignal,OutSignal);
    ntrials = ntrials+1;
    % Update the total number of errors.
    totErr = totErr + newerrs;
    % Update the total number of bits processed.
    numBits = ntrials*sigLen;
    
end % End of loop

% Compute the BER.
ber = totErr/numBits;