.text 0x00410000
#########################################################
# Faça um programa para buscar um determinado valor em um 
# array de inteiros. O endereço inicial do vetor está 
# armazenado no endereço de memória 0x10010000, o tamanho 
# do vetor está no endereço 0x10010004 e valor que será 
# pesquisado está no endereço 0x10010008. Caso o valor 
# seja encontrado, escreva 0x01 no endereço 0x1001000C, 
# caso contrário, escreva 0x00.
#
#########################################################
# bool vector_search(int * vector, int size, int value );
vector_search:
	li $v0, 0  ## return value
	vector_search_L0:
		beq $a1, $zero, vector_search_L0_end
			addi $a1, $a1, -1
			lw   $t0, 0($a0)
			bne  $t0, $a2, vector_search_skip
				li $v0, 1
				j  vector_search_L0_end
			vector_search_skip:
			addi $a0, $a0, 4 # vector++ (avanço para próx. elemento)
		b  vector_search_L0
	vector_search_L0_end:
	jr $ra
#########################################################
# Faça um programa para contar o número de elementos 
# encontrados em um array de inteiros. O endereço inicial 
# do vetor está armazenado no endereço de memória 0x10010000, 
# o tamanho do vetor está no endereço 0x10010004 e valor que 
# será contado está no endereço 0x10010008. Armazene no 
# endereço 0x1001000C o número de elementos encontrados 
# na procura.
#
#########################################################
# int vector_count(int * vector, int size, int value );
vector_count:
	li $v0, 0  ## return value
	vector_count_L0:
		beq $a1, $zero, vector_count_L0_end
			addi $a1, $a1, -1
			lw   $t0, 0($a0)
			bne  $t0, $a2, vector_count_skip
				addi $v0, $v0, 1
			vector_count_skip:
			addi $a0, $a0, 4 # vector++ (avanço para próx. elemento)
		b  vector_count_L0
	vector_count_L0_end:
	jr $ra
#########################################################
# Uma cadeia de caracteres (string) é definida como um 
# conjunto de bytes, ordenados de forma consecutiva na 
# memória, terminada por um caractere nulo (byte 0). Faça 
# um programa que receba o endereço do início de uma string 
# e calcule o seu tamanho (número de caracteres). O 
# endereço da string é armazenado no endereço 0x10010000. 
# Armazene o resultado no endereço de memória 0x10010004.
#
#########################################################
# int strlen(char * str)
strlen:
	li $v0, 0
	strlen_L0:
		lb $t0, 0($a0)
		beq $t0, $zero, strlen_L0_end
			addi $v0, $v0, 1
			addi $a0, $a0, 1
		j strlen_L0
	strlen_L0_end:
	jr $ra
#########################################################
# Faça um programa que receba dois endereços de memória 
# (fonte e destino) (0x10010000, 0x10010004), além da 
# quantidade de posições de memória (bytes) que devem 
# ser copiados (0x10010008), e faça a transferência dos 
# dados presentes no endereço de fonte, para o endereço 
# de destino.
#########################################################
# void memcpy(char * src, char * dest, int size)
memcpy:
	li $t1, 4
	memcpy_L0:
	blt $a2, $t1, memcpy_L0_end
		addi $a2, $a2, -4
		lw   $t0, 0($a0)
		sw   $t0, 0($a1)
		addi $a0, $a0, 4
		addi $a1, $a1, 4
	j memcpy_L0
  memcpy_L0_end:
  memcpy_L1:
  beq $a2, $zero, memcpy_L1_end
		addi $a2, $a2, -1
		lb   $t0, 0($a0)
		sb   $t0, 0($a1)
		addi $a0, $a0, 1
		addi $a1, $a1, 1
	j memcpy_L1
	memcpy_L1_end:
  jr $ra
#########################################################
# Paridade de uma palavra pode ser definida como par ou 
# ímpar, de acordo com a quantidade de bits “1” presentes 
# na palavra. Por exemplo, a palavra 0b0110 possui 
# paridade par, pois possui 2 bits ativados, enquanto que 
# a palavra 0b1110 possui paridade ímpar uma vez que possui 
# 3 bits ativados. Projete um programa em linguagem assembly 
# do MIPS para calcular a paridade da palavra presente no 
# endereço de memória 0x10018000. Armazene o valor 0x01 
# caso a paridade seja par, ou 0x02 caso seja ímpar no 
# endereço de memória 0x10018004.
#
# Utilize chamadas de sistemas para inicializar o valor 
# inicial da palavra armazenada no endereço 0x10018000.
#
#########################################################
# int paridade(int value)
paridade:
	li $v0, 0 # contador
paridade_L0:
	beq $a0, $zero, paridade_L0_end
		bgtz $a0, paridade_skip
			addi $v0, $v0, 1 # numero neg. -> bit 31 = 1
		paridade_skip:
		sll $a0, $a0, 1
	j paridade_L0
paridade_L0_end:
	andi $v0, $v0, 1
	addi $v0, $v0, 1
	jr $ra
	
#############################################	
# int strResize(char * str, int size);
#
#  O procedimento deve modificar o tamanho da string
# de acordo com o tamanho especificado pelo parâmetro
# size. O size deve ser sempre menor que o tamanho
# atual da string.
#
#  O procedimento retorna o valor -1, caso o size seja
# maior que o tamanho da string, ou o novo tamanho da
# string, caso contrário, ou seja, o próprio valor de
# size.
# ...
#-----------------
#  $a1 (strResize)  12($sp)
#-----------------
#  $a0 (strResize)  8($sp)
#=================
#  $ra              4($sp)
#-----------------
#  $a0 (strlen)     0($sp)
#-----------------
strResize:
	addi $sp, $sp, -8  # Crio o stack frame
	sw	$a1,  12($sp)
	sw  $a0,   8($sp)
	sw  $ra,   4($sp)  
	
	jal strlen
	move $t0, $v0
	lw   $a0, 8($sp)
	lw   $a1, 12($sp)
	
	blt $a1, $t0, strResize_IF0_then
		li $v0, -1 
		j strResize_end
strResize_IF0_then:  # Se for fazer o resize
		add $a0, $a0, $a1
		sb  $zero, 0($a0)
		move $v0, $a1
strResize_end:

	lw $ra, 4($sp)    # Restauro valor de $ra
	addi $sp, $sp, 8  # Destruo o quadro de pilha

	jr $ra
#############################################

###############################################
# unsigned int fatorial(unsigned int n){ 
#     if(n == 0) {
#         return 1; 
#     } else {
#         return n * fatorial(n-1); 
#     }
# }
#
#-----------------
#  $a0  (chamou fatorial) 8($sp)
#=================
#  $ra              4($sp)
#-----------------
#  $a0              0($sp)
#-----------------
###############################################
fatorial:
	addi $sp, $sp, -8
	sw   $ra, 4($sp)
	
	li $v0, 1
	beq $a0, $zero, fatorial_end
	sw   $a0, 8($sp)  # salvo $a0 na pilha de quem chamou fatorial
	addi $a0, $a0, -1
	jal fatorial
	lw   $a0, 8($sp)  # restauro o valor antigo de $a0
	mul  $v0, $a0, $v0
	
fatorial_end:
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
  jr $ra
###############################################
# char getchar();
getchar:
	la $t0, 0xFFFF0000   # Keyboard device base address
getchar_L0:
	lw   $t1, 0($t0)     # Load Keyboard Control Reg
	andi $t1, $t1, 0x01  # Isolo o bit 1
	beqz $t1, getchar_L0 # Se bit == 0, volto
	
	lb	$v0, 4($t0)		# Carrego o Keyboard Data

    jr $ra
###############################################
# void putchar(char value);
putchar:
	la $t0, 0xFFFF0008   # Display device base address
putchar_L0:
	lw   $t1, 0($t0)     # Load Display Control Reg
	andi $t1, $t1, 0x01  # Isolo o bit 1
	beqz $t1, putchar_L0 # Se bit == 0, volto
	
	sb	$a0, 4($t0)		# Carrego o Display Data

    jr $ra

  jr $ra
###############################################
# unsigned int fib(unsigned int n) 
####
# old_stak ($a0) <- 16($sp)
#---------------
# <empty>	     <- 12($sp)
#---------------
#  $ra			 <- 8($sp)
#---------------
#  $s0			 <- 4($sp)
#---------------
#  $a0			 <- 0($sp)
#---------------
fib:
	addiu $sp, $sp, -16
	sw    $s0, 4($sp)
	sw    $ra, 8($sp)
	sw    $a0, 16($sp)

	move $v0, $a0
	blt  $a0, 2, fib_end	
	
	addi $a0, $a0, -1
	jal  fib
	move $s0, $v0
	
	lw   $a0, 16($sp)
	addi $a0, $a0, -2
	jal  fib
	add  $v0, $s0, $v0
	
fib_end:
	lw    $s0, 4($sp)
	lw    $ra, 8($sp)
	addiu $sp, $sp, 16
	jr $ra




