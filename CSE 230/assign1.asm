# Name: Kumal Patel
# Class ID: 139
# Assignment Number: 1

.data
	.word 0 
	.word 0
	.word 0
	.asciiz "Kumal Patel"
	.asciiz "Enter a number " 
	.asciiz "\n"
.text
.globl main
main:
	# set resgister $s0 to 35
	addi $s0, $s0, 35
	
	# prompt user to enter a number, read it and store it in register $s1
	lui $a0, 0x1001
	addi $a0, $a0, 24
	addi $v0, $0, 4 # print string
	syscall
	addi $v0, $0, 5 # read int
	syscall
	addi $s1, $v0, 0 # stores input into $s1
	
	# prompt user to enter a number, read it and store it in register $s2
	lui $a0, 0x1001
	addi $a0, $a0, 24
	addi $v0, $0, 4 # print string
	syscall
	addi $v0, $0, 5 # read int
	syscall
	addi $s2, $v0, 0 # stores intput into $s2
	
	# store value of $s1 into 0x10010000
	sw $s1, 0x10010000
	
	# store value of $s2 into 0x10010004
	sw $s2, 0x10010004
	
	# calculate $s0 - $s1 + $s2 and store into memory location 0x1001008
	 sub $t0, $s0, $s1 # $s0 - $s1
	 add $t1, $t0, $s2  # $t0($s0 - $s1) + $s2
	 sw $t1, 0x10010008
	 
	 # print your name
	 lui $a0, 0x1001
	 addi $a0, $a0, 12
	 addi $v0, $0, 4 # Print name
	 syscall
	 
	 # print new line
	 lui $a0, 0x1001
	 addi $a0, $a0, 40
	 addi $v0, $0, 4
	 syscall
	 
	 # print the value in 0x10010000
	 lw $a0, 0x10010000
	 addi $v0, $0, 1
	 syscall
	 
	 # print new line
	 lui $a0, 0x1001
	 addi $a0, $a0, 40
	 addi $v0, $0, 4
	 syscall
	 
	 # print the value in 0x10010004
	 lw $a0, 0x10010004
	 addi $v0, $0, 1
	 syscall
	 
	 # print new line
	 lui $a0, 0x1001
	 addi $a0, $a0, 40
	 addi $v0, $0, 4
	 syscall
	 
	 # print the value in 0x10010008
	 lw $a0, 0x10010008
	 addi $v0, $0, 1
	 syscall
	 
	 # swap values in $s1 and $s2
	 addi $t2, $s1, 0 # set value in $s0 to an empty register ($t2)
	 addi $s1, $s2, 0 # set value in $s1 to value in $s2
	 addi $s2, $t2, 0 # set value in $s2 to value in $t2
	 
	 # set value of $s0 to -$s0
	 nor $s0, $s0, $0 # ones complement
	 addi $s0, $s0, 1 # twos complement -- results in negative of $s0 
	 addi $v0, $0, 10
	 syscall # stops program
