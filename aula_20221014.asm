.include "stdlib/system.inc"

.data
str: .asciiz "Hello World!\n"

.text 0x00401000
#=================
#  empty           12($sp)
#-----------------
#  $ra              8($sp)
#-----------------
#  $a1 				      4($sp)
#-----------------
#  $a0 			        0($sp)
#-----------------
main:
	addi $sp, $sp, -16
	sw   $ra, 8($sp)
	
	syscall_print_strMem(str)
	
	la $a0, str
	li $a1, 45
	jal strResize
	
	bltz $v0, main_error
		syscall_print_strMem(str)
		j main_exit
main_error:
		syscall_print_str("Erro, strResize retorno -1\n")
main_exit:
	
	lw $ra, 8($sp)
	addi $sp, $sp, 16
	jr $ra

	