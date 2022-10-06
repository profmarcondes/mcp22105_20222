# Code
#
# c = (a < b) || ( (a+b) == 10 )
#
# Mapeamento
#
# a: $t0, b: $t1, c: $t2
#

add  $t3, $t0, $t1 
addi $t4, $zero, 10
seq  $t3, $t3, $t4
slt  $t4, $t0, $t1
or   $t2, $t3, $t4







