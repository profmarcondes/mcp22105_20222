.kdata
_kexception_msg: .word _kexc_hardware, _kexc_unknown, _kexc_unknown , _kexc_unknown
		 		 .word _kexc_addrl, _kexc_addrs, _kexc_ibus , _kexc_dbus
		  		 .word _kexc_syscall, _kexc_bkpt, _kexc_ri , _kexc_unknown
		         .word _kexc_ovf, _kexc_trap, _kexc_unknown , _kexc_fpe
				 
_kexc_unknown:	.asciiz   "Exception Unknown\n"
_kexc_hardware:	.asciiz   "Hardware Interrupt\n"
_kexc_addrl:	.asciiz   "Address error exception caused by load or instruction fetch\n"
_kexc_addrs:	.asciiz   "Address error exception caused by store\n"
_kexc_ibus:		.asciiz   "Bus Error on instruction fetch\n"
_kexc_dbus:		.asciiz   "Bus Error on data load or store\n"
_kexc_syscall:	.asciiz   "Syscall exception\n"
_kexc_bkpt:		.asciiz   "Breakpoint exception\n"
_kexc_ri:		.asciiz   "Reserved instruction exception\n"
_kexc_ovf:		.asciiz   "Arithmetic overflow ocurred\n\n"
_kexc_trap:		.asciiz   "TRAP ocurred\n"
_kexc_fpe:		.asciiz   "Floating Point Exception\n"

.ktext 0x80000180
exception_handler:
	addiu	$sp, $sp, -132
	sw		$at,0($sp)
	sw		$v0,4($sp)
	sw		$v1,8($sp)
	sw		$a0,16($sp)
	sw		$a1,20($sp)
	sw		$a2,24($sp)
	sw		$a3,28($sp)
	sw		$t0,32($sp)
	sw		$t1,36($sp)
	sw		$t2,40($sp)
	sw		$t3,44($sp)
	sw		$t4,48($sp)
	sw		$t5,52($sp)
	sw		$t6,56($sp)
	sw		$t7,60($sp)
	sw		$s0,64($sp)
	sw		$s1,68($sp)
	sw		$s2,72($sp)
	sw		$s3,76($sp)
	sw		$s4,80($sp)
	sw		$s5,84($sp)
	sw		$s6,88($sp)
	sw		$s7,92($sp)
	sw		$t8,96($sp)
	sw		$t9,100($sp)
	sw		$k0,104($sp)
	sw		$k1,108($sp)
	sw		$gp,112($sp)
	sw		$fp,116($sp)
	sw		$ra,120($sp)
	mfhi    $k0
	sw		$k0,124($sp)
	mflo	$k0
	sw		$k0,128($sp)
	
	# Identificar a causa da excecão/interrupcão
	mfc0 	$k0, $13
	andi		$k0, $k0, 0x007C

	la  		$k1, _kexception_msg
	add 		$k1, $k1, $k0
	lw 		$a0, 0($k1)
	li 		$v0, 4
	syscall
	
	srl 		$k0, $k0, 2
	beqz 	$k0, exception_handler_Hardware

	bge  	$k0, 8, exception_handler_SoftException
	li 		$v0, 10
	syscall
	
exception_handler_SoftException:
	mfc0  	$k0, $14      # $k0 = EPC 
    addiu 	$k0, $k0, 4   # Increment $k0 by 4 
    mtc0  	$k0, $14      # EPC = point to next instruction
    j		exception_handler_Done 

exception_handler_Hardware:
	# Hardware Interrupt
	la   $t0, getchar
	jalr $t0
	move $a0, $v0
	la   $t0, putchar
	jalr $t0
	
exception_handler_Done:
	# Clear Cause register
	mtc0		$0, $13

	## restore registers
	lw		$at,0($sp)
	lw		$v0,4($sp)
	lw		$v1,8($sp)
	lw		$a0,16($sp)
	lw		$a1,20($sp)
	lw		$a2,24($sp)
	lw		$a3,28($sp)
	lw		$t0,32($sp)
	lw		$t1,36($sp)
	lw		$t2,40($sp)
	lw		$t3,44($sp)
	lw		$t4,48($sp)
	lw		$t5,52($sp)
	lw		$t6,56($sp)
	lw		$t7,60($sp)
	lw		$s0,64($sp)
	lw		$s1,68($sp)
	lw		$s2,72($sp)
	lw		$s3,76($sp)
	lw		$s4,80($sp)
	lw		$s5,84($sp)
	lw		$s6,88($sp)
	lw		$s7,92($sp)
	lw		$t8,96($sp)
	lw		$t9,100($sp)
	lw		$k0,104($sp)
	lw		$k1,108($sp)
	lw		$gp,112($sp)
	lw		$fp,116($sp)
	lw		$ra,120($sp)
	lw		$k0,124($sp)
	mthi    $k0
	lw		$k0,128($sp)
	mtlo	$k0
	addiu	$sp, $sp, 132
	eret
	
