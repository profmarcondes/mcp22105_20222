.include "stdlib/macros.inc"
.include "stdlib/stdlib.inc"

.data 0x10010000
vptr:  .word vector
size:  .word 8
value: .word 4
resp:  .word 0
count: .word 0

.data 0x10010100
vector: .word 3, 4, 67, 3, 4, 78, 99 , 4

.text 0x00400000
main:
	la $gp, 0x10010000
	
	
	syscall_print_str("Digite o valor a ser buscado:")
	syscall_get_intReg($a2)
	
	lw $a0, 0($gp)  # $a0 <- vptr (&vector)
	lw $a1, 4($gp)  # $a1 <- size
	sw $a2, 8($gp)  # $a2 -> value
	jal vector_search
	sw $v0, 12($gp) # armazeno o resultado em resp
	
	beq $v0, $zero, main_NotFound
		syscall_print_str("Valor encontrado!\n")
			lw $a0, 0($gp)  # $a0 <- vptr (&vector)
			lw $a1, 4($gp)  # $a1 <- size
			lw $a2, 8($gp)  # $a2 <- value
			jal vector_count
			sw $v0, 16($gp) # armazeno o resultado em count
			syscall_print_str("Encontrada ")
			syscall_print_intMem(count)
			syscall_print_str(" ocorrências.\n")
			
		j main_IF0_end
	main_NotFound:
		syscall_print_str("Valor não encontrado!\n")
	main_IF0_end:
	


	syscall_exit
