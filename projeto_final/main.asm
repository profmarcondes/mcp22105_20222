.include "system.inc"

animated_sprite(pacman, 3, 128, 128, 0, 0) 


.text 0x00401000

main:

main_L0:	
	## Draw sprite	
	la $a0, pacman
	jal draw_animated_sprite
	
	## Move sprite
	la  $a0, pacman
	jal apply_movement
	
	### Check input for move change
	la  $a0, pacman
	jal process_input
	
main_sleep:
	### sleep a little
	li $a0, 50
	li $v0, 32
	syscall 
	
	j main_L0
	