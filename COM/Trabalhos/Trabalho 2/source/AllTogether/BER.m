function Result=BER(In,Out)
    Result=sum(abs(In ~= Out));
    Result=Result/length(In);
end 