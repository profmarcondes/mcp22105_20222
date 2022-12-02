.include "stdlib/system.inc"

.text 0x00401000

# old stack    <- 16($sp)
#-------------
# $ra 			<- 12($sp)
#-------------
# $s1 			<- 8($sp)
#-------------
# $s0 			<- 4($sp)
#-------------
# $a0 			<- 0($sp)
#-------------
main:
	addiu $sp, $sp, -16
	sw 	  $s0, 4($sp)
	sw    $s1, 8($sp)
	sw    $ra, 12($sp)
	
main_L0:
	syscall_print_str("Valor = ")
	syscall_get_intReg($s0)
	
	bgt $s0, 10, main_end
	
	move $a0, $s0
	jal  fib
	move $s1, $v0
	
	syscall_print_str("fib(")
	syscall_print_intReg($s0)
	syscall_print_str(")=")
	syscall_print_intReg($s1)
	syscall_print_str("\n")

	j main_L0

main_end:
	lw 	  $s0, 4($sp)
	lw    $s1, 8($sp)
	lw    $ra, 12($sp)
	addiu $sp, $sp, 16
	jr $ra
