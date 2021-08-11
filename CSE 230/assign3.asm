# Name: Kumal Patel
# Class ID: 139
# Assignment Number: 3

.data
	num1: .word 0
	num2: .word 0
	answer: .asciiz "The product is "
	positive: .asciiz "Enter a positive number "
	newline: .asciiz "\n"
	
# add other strings at this point as needed

.text
.globl main

main:
	jal getpos # get a positive number for the loop
	addi $s0, $v0, 0 # save input value
repeat:
	beq $s0, $0, end # while there are more repeats

	lui $a0, 0x1001 # get address of first word
	addiu $a1, $a0, 4 # get address of second word
	jal getinput # call function to get input, store into addresses

	lui $t0, 0x1001 # get address of first word
	lw $a0, 0($t0) # get the first value from memory
	lw $a1, 4($t0) # get the second value from memory
	jal multiply # multiply the values, result in $v0

	addi $a0, $v0, 0 # get value to print from $v0
	lui $a1, 0x1001 # get start of data section
	addi $a1, $a1, 8 # get start of the product output string
	jal print # print results

	addi $s0, $s0, -1 # decrement counter
	j repeat # do it again
	
print:
	addi $t0, $v0, 0 # store value of $v0 into temp register $t0	
	
	addi $a0, $a1, 0 # load address of register $a1, which is the address of the string
	addi $v0, $0, 4 # set command to print string
	syscall # print string
	
	addi $a0, $t0, 0 # load in value in temp regiester $t0
	addi $v0, $0, 1 # set command to print int
	syscall # print int
	
	lui $t1, 0x1001 # get address of first word
	addi $t2, $t1, 49 # get address of newline
	addi $a0, $t2, 0 # get value to print from $t2
	addi $v0, $0, 4 # set command to print string
	syscall # print newline
	
	jr $ra
	
multiply:
	addi $t2, $0, 0 # set regiester $t0 to 0
	addi $v0, $0, 0 # restore register $v0 to 0
InLoop:
	beq $t2, $a1, OutLoop # while($t2 != $a1), else branch
	add $v0, $v0, $a0 # store value of $a0 + $v0 into $v0, eg. if $a0 = 2, 2+2..,$a1 times
	addi $t2, $t2, 1 # incremeent counter in register $t2
	j InLoop # loop back to top 	
OutLoop:
	jr $ra # return to the register address
	
getpos:
	lui $t3, 0x1001 # get address of first word
	addi $a0, $t3, 24 # get address of positive
	addi $v0, $0, 4 # set command to print string
	syscall # print positive
	
	addi $v0, $0, 5 # set command to read int
	syscall # read int
	
	bgt $v0, $0, return # if $v0 > 0
	j getpos # loop back if $v0 is not greater than 0
return:
	jr $ra # return to the register address
	 
getinput:
	addi $sp, $sp, -12
	sw $a0, 0($sp)
	sw $a1 4($sp)
	sw $ra, 8($sp)
	jal getpos
	addi $a0, $v0, 0
	jal getpos
	addi $a1, $v0, 0
	lw $a0, 0($sp)
	lw $a1, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra 
end: 
	ori $v0, $0, 10 # set command to stop program,
	syscall # end program
