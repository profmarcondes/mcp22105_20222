.text 0x00430000
#
#
#  int colors[8];
#  sprite sprites[20];
#  char sprite[49];
#=============================================================
# void draw_sprite(X, Y, sprite_id){
#       char * ptr_sprite =  sprites[sprite_id];
#       for(int i = 0; i < 49; i++){ 
#			color = colors[*ptr_sprite];
#           sX = i % 7 ;
#			sY = i / 7 ;
#           sX = X + sX;
#           sY = Y + sY;
#        	set_pixel(sX, sY, color)
#           ptr_sprite++;
#       }
# }
draw_sprite:

    jr   $ra
#=============================================================

#=============================================================
# void draw_animated_sprite(animated_sprite*)
draw_animated_sprite:
	addiu $sp, $sp, -16
	sw    $ra, 12($sp)
	
	move $t0, $a0
	lw   $a0, 4($t0)
	lw   $a1, 8($t0)
	lw   $a2, 0($t0)
	jal  draw_sprite

	lw    $ra, 12($sp)
	addiu $sp, $sp, 16
	jr    $ra
#=============================================================

#=============================================================
# void apply_movement(animated_sprite*)
apply_movement:
	## X movement
	lw  $t0, 12($a0)    # mov_x
	lw  $t1,  4($a0)    # pos_x
	add $t1, $t0, $t1   # pos_x = mov_x + pos_x
	sw  $t1,  4($a0)
	## Y movement
	lw  $t0, 16($a0)    # mov_y
	lw  $t1,  8($a0)    # pos_y
	add $t1, $t0, $t1   # pos_y = mov_y + pos_y
	sw  $t1,  8($a0)
	jr   $ra
#=============================================================

#=============================================================
# void set_move_animated_sprite(animated_sprite* sp, int vx, int vy)
set_move_animated_sprite:
	sw   $a1, 12($a0)
	sw   $a2, 16($a0)
	jr   $ra
#=============================================================

#=============================================================   
# void stop_animated_sprite(animated_sprite* sp)
stop_animated_sprite:
	sw   $zero, 12($a0)
	sw   $zero, 16($a0)
	jr   $ra
#=============================================================

#=============================================================
# char get_grid_element(row-y, column-x, grid_table* )
get_grid_element:
	## Le o elemento na grid table e retorna.
	jr  $ra
#=============================================================

#=============================================================
# draw_grid(width, height, grid_table* )
draw_grid:
	
	#Percorre a matriz da grid, para cada elemento
	
	## Pegar o id_do_sprite (get_grid_element)
	## converter de ASCII para ID (-64)
	## Chamar draw_sprite(grid pos -> pixel pos - multiplica {X|Y}_SCALE)
	
	jr   $ra
#=============================================================

# struct mov_vector {
#    int valid;
#    int mov_x;
#    int mov_y;
# }
#=============================================================
# process_input(mov_vector *)
process_input:

    ## Verificar se key_rb está vazio
    ## Se estiver, retornar
	
	## Senao
	## Le valor do ringbuffer
	
	## Processa valor com teclas associadas ao
	## movimento. Setar mov_vector e tornar
	## válido	
	
	jr   $ra
#=============================================================

#=============================================================   
# void try_change_movement(animated_sprite* sp, mov_vector* mv)
try_change_movement:

	## Verifica se muv_vector é válido
	## Se não, retorna.

	## Converte posição pixel para posicao grid
	## Lembrete - se resto divisao == 0, está alinhado
	
	## Se não está alinhado, não muda o movimento.
	## Retorna função.
	
	## Se alinhado, verifica se pode se mover para nova
	## direção
	
	## Calculo nova posicao somando vetor movimento
	## com posição do grid e pego elemento do grid
	## para ver se não é parede.
	
	## Se não for parede, aplica vetor de movimento
	## no sprite, caso contrário não faz nada
	## Não esquecer de tornar o mov_vector inválido
	## (valid = 0)
	
	jr   $ra
#=============================================================

#=============================================================
# bool check_movement(animated_sprite*)
check_movement:

	## Converte posição pixel para posicao grid
	## Lembrete - se resto divisao == 0, está alinhado
	
	## Se não está alinhado, pode se mover.
	## Retorna verdadeiro
	
	## Calculo nova posicao somando vetor movimento
	## com posição do grid e pego elemento do grid
	## para ver se não é parede.
	
	## Se não é parede retorna verdadeiro
	
	## Se for parede, para o sprite (stop_animated_sprite)
	## e retorna falso.

	jr   $ra
#=============================================================

