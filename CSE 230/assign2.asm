# Name: Kumal Patel
# Class ID: 139
# Assignment Number: 2

.data
	.word 0
	.word 0
	.word 0
	.asciiz "Kumal Patel" # 12
	.asciiz "Enter a number from 1 to 5: " # 24
	.asciiz "\n" # 53
	.asciiz "input is out of range" # 55
	.asciiz "Time = " #77
	.asciiz "Enter the first number: " # 85
	.asciiz "Enter the second number: " #110
	.asciiz "Even" # 136
	.asciiz "Odd" # 141
	.asciiz "Equal" # 145
	.asciiz "Less than" # 151
	.asciiz "Greater than" # 161
	.asciiz "Program complete" # 174
.text
.globl main
main:
	# print name
	lui $t0, 0x1001
	addi $a0, $t0, 12
	addi $v0, $0, 4
	syscall
	
	# print new line
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall  
	
	# print new line
	START:
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall 
	
	# prompt user to enter a number from 1 to 5
	addi $a0, $t0, 24
	addi $v0, $0, 4
	syscall  
	
	# read integer from user
	addi $v0, $0, 5
	syscall 
	
	# store input
	addi $t1, $v0, 0
	
	# check if input is within bounds, if not print that it isnt
	slti $t2, $t1, 6
	slt $t3, $1, $t1	
	beq $t2, $0, IF
	beq $t3, $0, IF
	j TOP
	 
	IF:
	addi $a0, $t0, 55
	addi $v0, $0, 4
	syscall
	j START
	
	# loop through $t1 times
	TOP:
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	addi $t4, $t4, 1
	addi $a0, $t0, 77
	addi $v0, $0, 4
	syscall # prints "Time = "
	addi $v0, $0, 1
	addi $a0, $t4, 0
	syscall # prints int after time
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	addi $a0, $t0, 85
	addi $v0, $0, 4
	syscall # prompts to enter first number
	addi $v0 $0, 5
	syscall # reads int
	addi $t5, $v0, 0 # stores int in $t5
	addi $a0, $t0, 110
	addi $v0, $0, 4
	syscall # prompts to enter second number
	addi $v0, $0, 5
	syscall # reads int
	addi $t6, $v0, 0 # stores int in $t6
	add $t7, $t5, $t6 # sum
	addi $s0, $0, 2 # divisor
	div $t7, $s0
	mfhi $s0 # saves remeainder
	beq $s0, $0, EVEN
	bne $s0, $0, ODD
	
	STOP:
	beq $t4, $t1, BOTTOM
	j TOP

	EVEN:
	addi $a0, $t0, 136
	addi $v0, $0, 4
	syscall
	j EXIT
	
	ODD:
	addi $a0, $t0, 141
	addi $v0, $0, 4
	syscall
	j EXIT
	
	EXIT:
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	slt $t8, $t5, $t6
	beq $t5, $t6, EQUAL
	bne $t8, $0, LESS
	beq $t8, $0, GREATER
	
	LESS:
	addi $a0, $t0, 151
	addi $v0, $0, 4
	syscall
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	j STOP
	
	GREATER:
	addi $a0, $t0, 161
	addi $v0, $0, 4
	syscall
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	j STOP
	
	EQUAL:
	addi $a0, $t0, 145
	addi $v0, $0, 4
	syscall
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall # prints new line
	j STOP
	   
	BOTTOM:
	addi $a0, $t0, 53
	addi $v0, $0, 4
	syscall 
	addi $a0, $t0, 174
	addi $v0, $0, 4
	syscall
	addi $v0, $0, 10
	syscall 
		
