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

.macro get_mem_Int (%int_ptr)
	li $v0, 5
	syscall
	sw $v0, %int_ptr
.end_macro

.data 
solicita_a: .asciiz "Entre com o valor de A: "
solicita_b: .asciiz "Entre com o valor de B: "
resultado:  .asciiz "O valor de A + B é: "
newline:    .asciiz "\n"
a: .word 0
b: .word 0
c: .word 0

.text
	la $gp, a

loop:

	printStr(solicita_a)
	get_mem_Int(a)
	
	printStr(solicita_b)
	get_mem_Int(b)
	
	lw $t0, 0($gp)
	lw $t1, 4($gp)
	add $t0, $t0, $t1
	sw $t0, 8($gp)
	
	printStr(resultado)
	print_mem_Int(c)
	printStr(newline)
	
	b loop
	
	exit
	

	
	
	
	
	
	
	
	
	




