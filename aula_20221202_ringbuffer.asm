.include "stdlib/system.inc"

.text 0x00401000

main:
	addi $s0, $s0, 1
	
	rem  $t0, $s0, 100000
	bnez $t0, main_skip
	syscall_print_str("Value of $s0 =")
	syscall_print_intReg($s0)
	syscall_print_str("\n")
	break
	
main_skip:
	la  $a0, key_rb
	jal rb_empty
	bnez $v0, main
	
	la  $a0, key_rb
	jal rb_read
	
	move $a0, $v0
	jal  putchar
	
	j main
	
	jr $ra
