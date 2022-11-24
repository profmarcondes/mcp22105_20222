.include "stdlib/system.inc"

.text 0x00401000

main:
	addi $s0, $s0, 1
	rem  $t0, $s0, 100000
	bnez $t0, main
	syscall_print_str("Value of $s0 =")
	syscall_print_intReg($s0)
	syscall_print_str("\n")
	break
	j main
	
	jr $ra
