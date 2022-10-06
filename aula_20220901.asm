.data 
num: .word 0, -1, 78
.data 0x10010100
sum: .word -99

.text 

la  $gp, num
lw  $t1, 0($gp)
lw  $t2, 4($gp)
lw  $t3, 8($gp)
add $t1, $t1, $t2
add $t1, $t1, $t3
sw  $t1, sum

