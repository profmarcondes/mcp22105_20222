.include "system.inc"

animated_sprite(pacman, 3, 128, 128, 0, 0) 

.data
move_vector:
	.word 0   #  valid
    .word 0   #  x_mov 
    .word 0   #  y_mov

.text 0x00401000

main:
	li $a0, GRID_ROWS
	li $a1, GRID_COLS
	la $a2, grid
	jal draw_grid
	
main_L0:	
	## Desenha o sprite animado	
	la $a0, pacman
	jal draw_animated_sprite
	
	## Verifica se posso mover ele
    ## Se não puder, para o sprite
	la  $a0, pacman
	jal check_movement
	
	## Aplica o vetor de movimento no sprite
	la  $a0, pacman
	jal apply_movement
	
	## Busca no teclado se há comando do user
	la  $a0, move_vector
	jal process_input
	
	## Tenta mudar o movimento se for possível
	la  $a0, pacman
	la  $a1, move_vector
	jal try_change_movement
	
main_sleep:
	### Dorme um pouquinho (usabilidade)
	syscall_sleep(30) 
	
	j main_L0
	