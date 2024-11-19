/*
Trabalho Pratico 2: Multiplicador Binário Sequencial
Thaís Ferreira da Silva - 2021092571
*/

`timescale 1ns/1ps //Usado para o clock

module trabalhoPratico2;

    //Dados iniciais
    reg Clock, Reset;
    reg [7:0] A; //Multiplicando
    reg [7:0] B; //Multiplicador
    wire [15:0] P; //Produto
	
  	integer count = 0;
  
    mbs uut(Clock, Reset, A, B, P);

	//clock comecando em 1
    initial begin
        Clock = 1'b1;
        while(count < 20) begin
           #1 Clock = ~Clock; //muda de 0 pra 1 ou de 1 pra 0
          count = count + 1;
        end
    end

    initial begin
        $dumpfile ("mbs.vcd");
        $dumpvars;
        
        //Caso de teste 1 (99*2)
        Reset = 1;
        A = 8'b01100011; 
        B = 8'b00000010;
      	#2;
		Reset = 0;
        #2;

        //Caso de teste 2 (3*44)
        Reset = 1;
        A = 8'b00000011;
        B = 8'b00101100;
      	#2;
		Reset = 0;
        #2;

        //Caso de teste 3 (69*24)
        Reset = 1;
        A = 8'b01000101;
        B = 8'b00011000;
      	#2;
		Reset = 0;
        #2;

        //Caso de teste 4 (80*100)
        Reset = 1;
        A = 8'b01010000;
        B = 8'b01100100;
      	#2;
		Reset = 0;
        #2;

        //Caso de teste 5 (32*200)
        Reset = 1;
        A = 8'b00100000;
        B = 8'b11001000;
      	#2;
		Reset = 0;
        #2;
    end

endmodule