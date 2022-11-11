.include "stdlib/system.inc"

.text 0x00401000

main:

	la $t0, 0x10010001
	lw $t0, 0($t0)       ## Acesso a mem desalinhado

	li $t0, 0x7FFFFFFF
	addi $t0, $t0, 1     ## Overflow
	
	break				## Break exception	
	
	jr $ra
