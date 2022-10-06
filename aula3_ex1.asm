# Code
# d = a - 3 * (b + c + 8)
#
# Mapeamento
# a: $t0, b: $t1, c: $t2, d: $t3
#
	add  $t3, $t1, $t2  # d = b + c
	addi $t3, $t3, 8   # d = d + 8 (b + c + 8)
	mul  $t3, $t3, 3   # d = d * 3 ( 3 * (b + c + 8))
	sub  $t3, $t0, $t3 # d = a - d ( a - 3 * (b + c + 8) )
	
	
	
	
	


