.macro exit
	li $v0, 10
	syscall
.end_macro

.macro printStr (%str_ptr)
	li $v0, 4
	la $a0, %str_ptr
	syscall
.end_macro

.macro printInt (%reg)
	li   $v0, 1
	move $a0, %reg
	syscall
.end_macro
.macro print_mem_Int (%int_ptr)
	li   $v0, 1
	lw   $a0, %int_ptr
	syscall
.end_macro

.macro getInt (%reg)
	li $v0, 5
	syscall
	move %reg, $v0
.end_macro

.macro getStr (%buf, %size)
	la $a0, %buf
	li $a1, %size
	li $v0, 8
	syscall
.end_macro

.macro get_mem_Int (%int_ptr)
	li $v0, 5
	syscall
	sw $v0, %int_ptr
.end_macro

.data

pergunta: .asciiz "Digite algo: "
seta: .asciiz " -> "
resposta: .asciiz "A string tem " 
resp2: .asciiz " caracteres \n"
tmp: .asciiz " *********** FIM *************** \n"
buffer: .space 1024

.text

	printStr(pergunta)
	getStr(buffer, 1024)
	
	la $a0, buffer  # seto o parametro com o endereco do buffer
	jal strlen
	move $s0, $v0
	
	printStr(resposta)
	printInt($s0)
	printStr(resp2)
	
	printStr(buffer)
	printStr(tmp)
	
	la $a0, pergunta
	jal strlen
	move $s0, $v0
	printInt($s0)
	
	printStr(pergunta) 
	printStr(seta) 
	printInt($s0)
	printStr(resp2)
	
	
	exit	
	
	
#  unsigned int strlen( char * str ) {
#       unsigned int len = 0;
#       while(*str != '\0'){
#				   len++;
#          str++;
#       }
#       return len;
#  }
strlen:
	addi $v0, $zero, 0 ## len = 0
	strlen_L0:
		lb $t0, 0($a0) # Carrego t0 = *str
		beqz $t0, strlen_L0_end
			addi $v0, $v0, 1  # len++
			addi $a0, $a0, 1  # str++
		j strlen_L0
	strlen_L0_end:
	jr $ra

