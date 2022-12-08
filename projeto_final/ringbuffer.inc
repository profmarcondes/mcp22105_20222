.eqv RB_MAX_SIZE 16

.text
#define MAX_SIZE 16

#typedef struct ringbuffer {
#	int size;
#	int rd;
#	int wr;
#	char buf[MAX_SIZE];
#} t_ringbuffer;

# void rb_init(t_ringbuffer * rbuf){
# 	rbuf->size = 0;
# 	rbuf->rd = 0;
# 	rbuf->wr = 0;
# }
rb_init:
	sw $zero, 0($a0)
	sw $zero, 4($a0)
	sw $zero, 8($a0)
	jr $ra

# bool rb_empty(t_ringbuffer * rbuf){
#	if (rbuf->size == 0) {
#		return 1;
#	} else {
#		return 0;
#	}
# }
rb_empty:
	lw   $t0, 0($a0)
	seq  $v0, $t0, $zero
	jr   $ra

# bool rb_full(t_ringbuffer * rbuf){
#	if (rbuf->size == MAX_SIZE)
#		return 1;
#	else
#		return 0;
# } 
rb_full:
	lw   $t0, 0($a0)
	seq  $v0, $t0, RB_MAX_SIZE
	jr   $ra
	
#char rb_read(t_ringbuffer * rbuf){
#	char tmp = 0;
#	if(!rbuf_empty(rbuf)){
#		rbuf->size--;
#		tmp = rbuf->buf[rbuf->rd];
#		rbuf->rd = (rbuf->rd + 1) % MAX_SIZE;
#	}
#	return tmp;
#}
rb_read:
	move $v0, $zero
	lw   $t0, 0($a0)
	beqz $t0, rb_read_end
	addi $t0, $t0, -1
	sw   $t0, 0($a0)   # rbuf->size--
	
	lw   $t0, 4($a0)   # rbuf->rd
	add  $t1, $t0, $a0 #
	lb   $v0, 12($t1)  # tmp = rbuf->buf[rbuf->rd];
	
	addi $t0, $t0, 1            # rbuf->rd++
	rem  $t0, $t0, RB_MAX_SIZE  # rbuf->rd++ % RB_MAX_SIZE
	sw   $t0, 4($a0)            #
	
rb_read_end:
	jr $ra

# bool rb_write(t_ringbuffer * rbuf, char byte){
#	if(!rbuf_full(rbuf)){
#		rbuf->size++;
#		rbuf->buf[rbuf->wr] = byte;
#		rbuf->wr = (rbuf->wr + 1) % MAX_SIZE;
#		return 1;
#	}
#	return 0;
# }
rb_write:
	move $v0, $zero
	lw   $t0, 0($a0)
	beq  $t0, RB_MAX_SIZE, rb_write_end
	
	addi $t0, $t0, 1
	sw   $t0, 0($a0)   # rbuf->size++
	
	lw   $t0, 8($a0)   # rbuf->wr
	add  $t1, $t0, $a0 #
	sb   $a1, 12($t1)  # rbuf->buf[rbuf->wr] = byte;
	
	addi $t0, $t0, 1            # rbuf->wr++
	rem  $t0, $t0, RB_MAX_SIZE  # rbuf->wr++ % RB_MAX_SIZE
	sw   $t0, 8($a0)            #
	
rb_write_end:
	jr $ra
