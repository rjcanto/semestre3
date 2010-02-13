function Result=BER(In,Out)
    Result=sum(abs(In ~= Out));
end 