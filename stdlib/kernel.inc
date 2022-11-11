.kdata
exception_msg: .asciiz "\n\n Ocorreu uma exceção!!!\n\n"
.align 2
k_save_regs: .space 12

.ktext 0x80000180
exception_handler:
	move $k0, $at
	la   $k1, k_save_regs
	
	sw   $k0, 0($k1)
	sw   $v0, 4($k1)
	sw   $a0, 8($k1)
		
	li $v0, 4
	la $a0, exception_msg
	syscall
	
	mfc0 $k0, $14     # move EPC para $k0
	addi $k0, $k0, 4  # Aponto para a próxima instrução
	mtc0 $k0, $14     # atualiza valor no EPC
	
	lw   $at, 0($k1)
	lw   $v0, 4($k1)
	lw   $a0, 8($k1)
	
	eret


