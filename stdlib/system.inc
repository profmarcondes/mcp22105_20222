.include "macros.inc"
.include "stdlib.inc"
.include "ringbuffer.inc"
.include "kernel.inc"

.eqv STACK_INIT 0x7FFFEFFC

.data
.align 2
key_rb: .space 28

.text 0x00400000 ## System Init Code
init:
	la $sp, STACK_INIT
	
	la   $a0, key_rb
	jal  rb_init
	jal  enable_keyboard_int
	
	jal main
	syscall_exit
	
.text 0x00420000  ## System lib
#=============================================================
# void enable_int
enable_int:
	mfc0	$t0, $12
	ori     $t0, $t0, 0x0001
	mtc0    $t0, $12
	jr 		$ra

#=============================================================
# void disable_int
disable_int:
	mfc0	$t0, $12
	andi    $t0, $t0, 0xFFFE
	mtc0    $t0, $12
	jr 		$ra

#=============================================================
# void enable_irq(int irq_num)
enable_irq:
	mfc0    $t0, $12
	li      $t1, 1
	addi    $a0, $a0, 8
	sllv 	$t1, $t1, $a0
	or      $t0, $t0, $t1
	mtc0    $t0, $12
	jr 		$ra

#=============================================================
# void disable_irq(int irq_num)
disable_irq:
	mfc0    $t0, $12
	li      $t1, 1
	addi    $a0, $a0, 8
	sllv 	$t1, $t1, $a0
	not 	$t1, $t1
	and     $t0, $t0, $t1
	mtc0    $t0, $12
	jr 		$ra

#=============================================================
# void enable_keyboard_int
enable_keyboard_int:
	addiu   $sp, $sp, -8
	sw      $ra, 4($sp)

	jal 	disable_int
	
	la		$t0, 0xFFFF0000  # Keyboard Control Reg.
	lw		$t1, 0($t0)
	ori     $t1, $t1, 0x0002
	sw      $t1, 0($t0) 
	
	li      $a0, 0
	jal     enable_irq
	
	jal     enable_int

	lw      $ra, 4($sp)
	addiu   $sp, $sp, 8
	jr 		$ra	
#=============================================================
