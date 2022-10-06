# Code
#
# c = (a < b) && (((a+b) % 3) == 2) 
#
# Mapeamento
#
# a: $t0, b: $t1, c: $t2
#

add  $t3, $t0, $t1  # a+b
addi $t4, $zero, 3  # t4 <- 3
div  $t3, $t4
mfhi $t3
li   $t4, 2
seq  $t3, $t3, $t4 
slt  $t2, $t0, $t1
and  $t2, $t2, $t3



