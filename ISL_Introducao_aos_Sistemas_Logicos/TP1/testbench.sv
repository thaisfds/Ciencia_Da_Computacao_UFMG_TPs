module trabalhoPratico1;
    reg[3:0] grayIn; //Entrada gray
    wire[3:0] binOut; //Saida bin

    grayToBin uut(grayIn,binOut);

    initial begin
        $dumpfile("dump.vcd"); $dumpvars; //Requisito do EPWave

        //Entradas gray
        grayIn = 4'b0000; #1;
        grayIn = 4'b0001; #1;
        grayIn = 4'b0011; #1;
        grayIn = 4'b0010; #1;
        grayIn = 4'b0110; #1;
        grayIn = 4'b0111; #1;
        grayIn = 4'b0101; #1;
        grayIn = 4'b0100; #1;
        grayIn = 4'b1100; #1;
        grayIn = 4'b1101; #1;
        grayIn = 4'b1111; #1;
        grayIn = 4'b1110; #1;
        grayIn = 4'b1010; #1;
        grayIn = 4'b1011; #1;
        grayIn = 4'b1001; #1;
        grayIn = 4'b1000; #1;
        
    end

endmodule