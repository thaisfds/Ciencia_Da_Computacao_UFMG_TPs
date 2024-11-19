/*
Trabalho Pratico 1: O Codigo de Gray
Thaís Ferreira da Silva - 2021092571
*/

module grayToBin(gray, bin);

    input [3:0] gray;
    input [3:0] bin;

    wire [3:0] grayInv; //gray invertido
    wire [1:0] x; // Entradas para b2
    wire [3:0] y; // Entradas para b1
    wire [7:0] z; // Entradas para b0

    //Invertendo gray
    not (grayInv[0],gray[0]);
    not (grayInv[1],gray[1]);
    not (grayInv[2],gray[2]);
    not (grayInv[3],gray[3]);

    //b3 = (g3)
    buf (bin[3], gray[3]); 

    //b2 = (!g3&g2) | (g3&!g2)
    and (x[0],grayInv[3],gray[2]);
    and (x[1],gray[3],grayInv[2]);
    or(bin[2],x[0],x[1]); 

    //b1 = (!g3&g2&!g1) | (!g3&!g2&g1) |
    // (g3&!g2&!g1) | (g3&g2&g1)
    and(y[0],grayInv[3],gray[2],grayInv[1]);
    and(y[1],grayInv[3],grayInv[2],gray[1]);
    and(y[2],gray[3],grayInv[2],grayInv[1]);
    and(y[3],gray[3],gray[2],gray[1]);
    or(bin[1],y[0],y[1],y[2],y[3]);

    //b0 = (!g3&g2&!g1&!g0) | (!g3&!g2&g1&!g0) |
    // (!g3&!g2&!g1&g0) | (!g3&g2&g1&g0) |
    // (g3&!g2&!g1&!g0) | (g3&g2&g1&!g0) |
    // (g3&g2&!g1&g0) | (g3&!g2&g1&g0);
    and(z[0],grayInv[3],gray[2],grayInv[1],grayInv[0]);
    and(z[1],grayInv[3],grayInv[2],gray[1],grayInv[0]);
    and(z[2],grayInv[3],grayInv[2],grayInv[1],gray[0]);
    and(z[3],grayInv[3],gray[2],gray[1],gray[0]);
    and(z[4],gray[3],grayInv[2],grayInv[1],grayInv[0]);
    and(z[5],gray[3],gray[2],gray[1],grayInv[0]);
    and(z[6],gray[3],gray[2],grayInv[1],gray[0]);
    and(z[7],gray[3],grayInv[2],gray[1],gray[0]);
    or(bin[0],z[0],z[1],z[2],z[3],z[4],z[5],z[6],z[7]);

endmodule