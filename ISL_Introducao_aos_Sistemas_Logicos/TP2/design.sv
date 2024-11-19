/*
Trabalho Pratico 2: Multiplicador Binário Sequencial
Thaís Ferreira da Silva - 2021092571
*/

`timescale 1ns/1ps //Usado para o clock

module mbs (Clock, Start, B, A, P);

	//Dados iniciais
	input Clock, Start;
	input [7:0] B; //Multiplicando
	input [7:0] A; //Multiplicador
	output reg [15:0] P; //Produto

	//Variaveis auxiliares
	integer count;
	reg [15:0] MultB; //Auxiliar para Multiplicando
	reg [7:0] MultA; //Auxiliar para Multiplicador

	always@(posedge Clock) begin
		//t = 0 (start) carrega as entradas
		if(Start) begin
			P = 0;
			MultB[7:0] = B;
			MultB[15:8] = 0; //completa os outros espacos com zeros
			MultA = A;
			count = 0;
		end
		
		//t != 0 realiza as operaçoes
		else begin
			while(count < 8) begin
				if(MultA[0] == 1'b1) begin
					P = P + MultB;
				end
				MultB = MultB << 1; //Desloca para a esquerda
				MultA = MultA >> 1; //Desloca para a direita
				count = count + 1; //Aumenta o contador de deslocamento
			end
		end
	end

endmodule