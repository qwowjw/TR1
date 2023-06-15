function signal = fsk(A, f1, f2, bot_stream)

    sig_size = lenght(bit_stream);
    signal = zeros(1,sig_size*100);

    for i=1:sig_size
        if (bit_stream(i) ==1)
            for j=1:100
                signal((i-1)*100+j) = A*sin(2*pi*f1*j/100);
            end
        else
            for j=1:100
                signal ((i-1)*100+j) = A*sin(2*pi*f2*j/100);
            end
        end
    end