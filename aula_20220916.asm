.macro exit
	li $v0, 10
	syscall
.end_macro

.macro printStr (%str_ptr)
	li $v0, 4
	la $a0, %str_ptr
	syscall
.end_macro

.macro printFloat (%reg)
	li    $v0, 2
	mov.s $f12, %reg
	syscall
.end_macro

.macro printInt (%reg)
	li   $v0, 1
	move $a0, %reg
	syscall
.end_macro

.macro print_mem_Int (%int_ptr)
	li   $v0, 1
	lw   $a0, %int_ptr
	syscall
.end_macro

.macro getInt (%reg)
	li $v0, 5
	syscall
	move %reg, $v0
.end_macro

.macro getFloat (%reg)
	li $v0, 6
	syscall
	mov.s %reg, $f0
.end_macro

.macro get_mem_Int (%int_ptr)
	li $v0, 5
	syscall
	sw $v0, %int_ptr
.end_macro

.data
notas: .float 0.0, 0.0, 0.0

input: .asciiz "Entre com a nota "
temp:  .asciiz ":"
media: .asciiz "A média calculada foi: "

repr: .asciiz "- Reprovado\n"
aprv: .asciiz "- Aprovado\n"

.text
  la   $gp, notas
  
  #for(int i = 0; i < 3; i++){
  #   printf("Entre com a nota %d:", i);  
  #   notas[i] = getFloat();
  #}
 	li $t0, 0
  L0:
  	bge $t0, 3, L0_end
  		printStr(input)
  		printInt($t0)
  		printStr(temp)
  		getFloat($f1)
  		sll  $t1, $t0, 2    # i * 4
  		add  $t1, $t1, $gp  # &notas[i] (end_base + offset)
  		swc1 $f1, 0($t1)
   	addi $t0, $t0, 1
  	j L0
  L0_end: 
  
	lwc1 $f1, 0($gp)
	lwc1 $f2, 4($gp)
	lwc1 $f3, 8($gp)
	
	add.s $f0, $f1, $f2
	add.s $f0, $f0, $f3
	
	li    $t0, 3
	mtc1  $t0, $f4
	cvt.s.w $f4, $f4
	
	div.s $f0, $f0, $f4
	
	printStr(media)
	printFloat($f0)
	
	li    $t0, 6
	mtc1  $t0, $f4
	cvt.s.w $f4, $f4
	
	c.lt.s 2, $f0, $f4

IF0:
	bc1t 2, IF0_else
		printStr(aprv)
		j IF0_end	
IF0_else:
		printStr(repr)
IF0_end:

	exit
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



