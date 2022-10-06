.data 0x10010001
num: .space 4

.text

lh $t0, num

li $v0, 10
syscall