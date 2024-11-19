.data
cartao: .word 4 9 1 6 6 4 1 8 5 9 3 6 9 0 8 0
##### START MODIFIQUE AQUI START #####

base: .word 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1

# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
la a0, cartao
jal ra, verifica
beq zero,zero,FIM
##### START MODIFIQUE AQUI START #####

#Parte 1#
verifica:   addi sp, sp, -8 #reserva espaço na pilha
            sw ra, 0(sp) #salva o endereço de retorno na pilha
            la a1, base #pega o vetor base para multiplicacao
            lw a2, 60(a0) #pega o ultimo numero do cartao na posicao 15*4
            addi a3, zero, 0 #soma dos digitos
            jal ra, multvetores

            addi t1, zero ,10
            rem t0, a3, t1  #resto da soma/10
            sub t2, t1, t0  #10 - resto

            addi a0, zero, 0 #cartao comeca invalido

            bne t2, t1, VALIDA
            addi t2, zero, 0 #se o resto for 0, 10-0 = 10. Entao mudamos pra 0

VALIDA:     bne a2, t2, RETURN
            addi a0, zero, 1 #cartao valido          

RETURN:     lw ra, 0(sp) #carrega o retorno
            addi sp, sp, 8
            jalr zero, 0(ra)

#Parte 2#
multvetores:
            addi t0, zero, 0 #Armazena a soma temporario
            addi t5, zero, 0 #interador do loop = i

LOOP1:      lw t1, 0(a0) #muda o numero do cartao
            lw t2, 0(a1) #muda o numero na base
            mul t3, t1, t2 #multiplica a0 por a1

            addi t6, zero, 10 #Armazena o mod e o tamanho do cartao
            blt t3, t6, SOMA #menor que 10
            rem t4, t3, t6 #pega o digito a direita ex. 6 para 16
            div t3, t3, t6 #pega o digito a esquerda ex. 1 para 16
            add t3, t3, t4 #soma os dois digitos ex. 6+1 = 7
            
SOMA:       add t0, t0, t3 #soma a multiplicacao no retorno

            addi a0, a0, 4 #muda o numero do cartao
            addi a1, a1, 4 #muda o numero na base
            addi t5, t5, 1 #incrementa i

            addi t6, zero, 15 #Armazena o mod e o tamanho do cartao
            blt t5, t6, LOOP1

            addi a3, t0, 0 #retorna a soma
            jalr zero, 0(ra)


##### END MODIFIQUE AQUI END #####
FIM: add zero, zero, zero