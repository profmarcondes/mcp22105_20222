.include "macros.inc"
.include "stdlib.inc"

.eqv STACK_INIT 0x7FFFEFFC

.text 0x00400000
init:
	la $sp, STACK_INIT
	jal main
	syscall_exit
	