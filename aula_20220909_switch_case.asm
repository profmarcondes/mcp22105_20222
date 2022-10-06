.macro exit
	li $v0, 10
	syscall
.end_macro

.macro printStr (%str_ptr)
	li $v0, 4
	la $a0, %str_ptr
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

.macro get_mem_Int (%int_ptr)
	li $v0, 5
	syscall
	sw $v0, %int_ptr
.end_macro

.data
jump_table: .word case_0, case_1, case_2, case_3, case_4
            .word case_5, case_6, case_7, case_8, case_9

insert_str: .asciiz "Entre com um número de 0 a 9: "
zero: .asciiz "n é zero\n"
par:  .asciiz "n é par\n"
quadrado: .asciiz "n é quadrado\n"
primo: .asciiz "n é número primo\n"
default_str: .asciiz "n fora dos limites [0,9]\n\n"

.text
main:
	printStr(insert_str)
	getInt($s0)

	switch_case:
		## verificar e fazer o salto do switch-case
		sltiu	$t0, $s0, 10
		beq   $t0, $zero, default
		
		sll   $t0, $s0, 2  # n * 4
		la    $t1, jump_table
		add 	$t0, $t1, $t0  # &jump_table[n]
		lw    $t0, 0($t0)    # t0 <- jump_table[n]
		jr    $t0

		case_0:
			printStr(zero)
			j switch_case_end
		case_4:
			printStr(par)
		case_1:
		case_9:
			printStr(quadrado)
			j switch_case_end
		case_2:
			printStr(par)
		case_3:
		case_5:
		case_7:
			printStr(primo)
			j switch_case_end
		case_6:
		case_8:
			printStr(par)
			j switch_case_end
		default:
			printStr(default_str)
	switch_case_end:
	
	j main







