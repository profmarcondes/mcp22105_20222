# if ( a < 10 ) {
#   b = 20;
#   if ( a <= 5 ){
#  	  for ( int i = 0; i < a; i++)
#         b += a * i;
#   } else {
#     while ( a-- > 5) {
#         b -= b / a;
#			}
#   }
#}
#// Mapeamento de registradores
#// a -> $s0 , b -> $s1

IF0: 
	li $t0, 10
	bge $s0, $t0, IF0_end
	li  $s1, 20             # b = 20
	IF1:
		bgt $s0, 5, IF1_else
	  	# inicialização do for
	  	li $t0, 0 # int i = 0
	  	L0:  
	  		bge $t0, $s0, L0_end # teste condição
	  		# corpo L0
	  		mul $t1, $s0, $t0   # tmp = a*i
	  		add $s1, $s1, $t1   # b += tmp (b = b + tmp)
	  		addi $t0, $t0, 1 # update (i++)
	  		j L0
	  	L0_end:
		j IF1_end
	IF1_else:
		L1:
			addi $s0, $s0, -1   # a--
			slti $t0, $s0, 5    # a <= 5
			bne  $t0, $zero, L1_end
			# corpo L1
			div  $s1, $s0
			mflo $t0						# tmp = b / a
			sub  $s1, $s1, $t0  # b -= tmp ( b = b - tmp )
			j L1
		L1_end:
	IF1_end:
IF0_end:



