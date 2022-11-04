.include "stdlib/system.inc"

.text 0x00401000

main:

	jal getchar
	move $a0, $v0
	jal putchar
	
	j	main

	jr $ra
