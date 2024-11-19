.data
vetor: .word 0 0 0 0
##### START MODIFIQUE AQUI START #####
#
# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
add s0, zero, zero
#Teste 1
        addi a0, zero, 5
        addi a1, zero, 7
        la a2, vetor
        jal ra, primos
        addi t0, zero, 2
        beq t0, a0, OK1
        beq zero, zero, T2
OK1:    addi s0, s0, 1 #Teste ok, passou
#Teste 2
T2:     addi a0, zero, 1
        addi a1, zero, 6
        la a2, vetor
        jal ra, primos
        addi t0, zero, 3
        beq t0, a0, OK2
        beq zero,zero, FIM
OK2:    addi s0, s0, 1 #Teste ok, passou
        beq zero,zero, FIM
##### START MODIFIQUE AQUI START #####
#Verifica se ha numeros negativos, ou a1 < a0#
primos: blt a0, x0, FIMP
        blt a1, x0, FIMP
        blt a1, a0, FIMP

        addi t0 , zero , 0 # verificador = 0;
        addi t1 , zero , 0 # numerosPrimos = 0;
        #Inicio Loop1#
        add t2 , zero , a0 # i = a0; 
LOOP1:  addi t3 , zero , 2 # j = 2;

        #Verifica se i == 0#
        addi t4 , zero, 0
        bne t2 , t4, VERIF3 
        addi t0 , zero , 1  

        #Verifica se i == 1#
VERIF3: addi t4 , zero, 1
        bne t2 , t4, VERIF4
        addi t0 , zero , 1

        #Verifica se i == 2#
VERIF4: addi t4 , zero, 2
        bne t2 , t4, VERIF5
        addi t0 , zero , 0

        #Verifica se i < 3 e vai pra validacao de primos#
VERIF5: addi t4 , zero, 3 
        blt t2, t4, VERIF1
        
        #Inicio Loop2#
LOOP2:  rem t4, t2, t3 
        bne t4, zero, SOMAJ # if(i%j != 0) goto SOMAJ;
        addi t0, zero, 1 # verificador = 1;
SOMAJ:  addi t3, t3, 1 # j++;  
        blt t3, t2, LOOP2 # if(j < i) goto LOOP2;

VERIF1: bne t0, zero, VERIF2 # if(verificador != 0) goto VERIFICADOR2;
        sw t2 , 0(a2) # a2.push_back(i);
        addi a2 , a2 , 4 # 
        addi t1 , t1, 1 # numerosPrimos++; 
VERIF2: addi t0 , zero , 0 # verificador = 0; 
        addi t2, t2, 1 # i++;
        addi t4, a1, 1 # 
        blt t2, t4, LOOP1 # if(i < a1+1) goto LOOP1;

FIMP:   addi a0, t1, 0  # fim da funcao primos
        jalr zero 0(ra) # return numerosPrimos;  
#
##### END MODIFIQUE AQUI END #####
FIM:    add zero, zero, zero
#Final da execucao, s0 deve ter o valor igual a 2.
