.include "stdlib/system.inc"

.text 0x00401000
#  old_stack     16
# =============
#  $ra           12($sp)
# -------------
#  $s1           8($sp)
# -------------
#  $s0           4($sp)
# -------------
#  $a0           0($sp)
###############
main:
  addi $sp, $sp, -16
  sw   $s0,  4($sp)
  sw   $s1,  8($sp)
  sw   $ra, 12($sp)

	li $s0, 11
main_L0:
	beqz $s0, main_L0_end
	addi $s0, $s0, -1
	
	syscall_print_str("fatorial(")
	syscall_print_intReg($s0)
	syscall_print_str(") = ")
	
	move $a0, $s0
	jal  fatorial
	move $s1, $v0
	
	syscall_print_intReg($s1)
	syscall_print_str("\n")
	
	j main_L0
	
main_L0_end:

	lw   $ra, 12($sp)
	lw   $s1,  8($sp)
	lw   $s0,  4($sp)
	addi $sp, $sp, 16

	jr $ra