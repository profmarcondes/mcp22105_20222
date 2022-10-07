.include "stdlib/macros.inc"
.include "stdlib/stdlib.inc"

.data 
valor:    .word 0
result: .word 0

.text 0x00400000
main:
	la $gp, 0x10010000
	
	syscall_print_str("Digite o valor para o cálculo de paridade:")
	syscall_get_intReg($a0)
	sw $a0, 0($gp) # salvo entrada do usuario em valor
	jal paridade
	sw $v0, 4($gp) # salvo retorno em paridade
	
	syscall_print_str("A paridade do valor ")
	syscall_print_intMem(valor)
	syscall_print_str(" é ")
	
	lw $t0, 4($gp)
	beq $t0, 1, paridade_par
		syscall_print_str("ímpar.\n")
	j if_end
	paridade_par:
		syscall_print_str("par.\n")
	if_end:
	
	syscall_exit