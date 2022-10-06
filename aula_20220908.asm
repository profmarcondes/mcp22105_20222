# total-> $t0, i-> $t1, n->  $t2
# total = 0
# 
#  for (i=0; i < n; i++){
#		if (i%5 > 2) continue;
#   total += i;
# }
	li $t0, 0    # total = 0
	
	li $t5, 5    # t5 -> constante 5
	li $t4, 2    # t4 -> constante 2
	li $t1, 0    # i = 0
LO:	bge $t1, $t2, LO_end
	  IF0:
	  	div  $t1, $t5  # div i / 5
	  	mfhi $t3       # $t3 <- i%5
	  	bgt  $t3, $t4, L0_update
	  IF0_end:
		add $t0, $t0, $t1   # total += i
L0_update:
		addi $t1, $t1, 1   # i++ ( i = i + 1 )
		j L0
L0_end:






