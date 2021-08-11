# Name: Kumal Patel
# Class ID: 139
# Assignment Number: 4
.data
	name: .asciiz "Kumal Patel" # 0x10010000
	newLine: .asciiz "\n" # 0x1001000C
	number: .asciiz "Enter a number " # 0x1001000E
		.space 1
	array: .space 40 # 0x10010020

.globl main
.text

main:
	# print name
	lui $t0, 0x1001 # base register of address for global data
	addi $a0, $t0, 0 # set address location of name in $a0
	ori $v0, $0, 4 # set command to print string
	syscall # print string
	
	addi $a0, $t0, 0x20 # address of array
	jal readvals # call readvals
	
	addi $a0, $t0, 0x20 # address of array
	addi $a1, $t2, 0 # count
	jal average # call average
	
	addi $a0, $t0, 0x20 # address of array
	addi $a1, $t2, 0 # count
	jal print # call print
	
	ori $v0, $0, 10 # set command to end program
	syscall # end program
	
readvals:
	ori $t1, $0, 0 # used for if < 0
	ori $t2, $0, 0 # count constant
	addi $t3, $0, 10 # constant value
	ori $t5, $0, 0 # keep track of memory location
	
	ori $t7, $a0, 0 # argument
		
	addi $a0, $t0, 12 # set address of newLine in $a0
	ori $v0, $0, 4 # set command to print string
	syscall # print string
top:	
	addi $a0, $t0, 14  # set address of number in $a0
	ori $v0, $0, 4 # set command to print string
	syscall # print stirng

	ori $v0, $0, 5 # set command to read int
	syscall # read int

	slt $t4, $v0, $t1 # if ($v0 < 0)
	
	bne  $t4, $0, bottom # bottom if ($t4 != 0)
	beq $t2, $t3, bottom # bottom if ($t2 == 10)
	addi $t2, $t2, 1 # $t2++
	j store # jump to store	
store:
	sll $t6, $t5, 2 # mult by 4
	addu $t6, $t6, $t7 # get address
	sw $v0, 0($t6) # store value in array
	addi $t5, $t5, 1 # $t5+ 
	j top	 # jump to top
bottom:
	jr $ra # return register address
average:
	ori $t1, $0, 0 # track total
	ori $t2, $0, 0 # index count
top2:
	slt $t3, $t2, $a1 # index < $a1
	beq $t3, $0, end # branch if > $a1
	sll $t3, $t2, 2 # mult by 4
	addu $t3, $t3, $a0 # get address
	lw $t3, 0($t3) # get word
	add $t1, $t1, $t3 # add to total
	addi $t2, $t2, 1 # index it
	j top2 # jump to top2
end:
	mtc1 $t1, $f4 # move to coproccesor 
	cvt.s.w $f4, $f4 # store total in $f4
	mtc1 $t2, $f6 # move to coprocessor
	cvt.s.w $f6, $f6 # store count in $f6
	div.s $f0, $f4, $f6 # store result of average in $f0
	j exit # jump to exit
exit:
	jr $ra # return register address
print:
 	ori $t0, $0, 0 # track count
 	ori $t2, $a0, 0 # argument
 	lui $t3, 0x1001 # base reg for global data
top3:
	slt $t1, $t0, $a1 # index < $a1
	beq $t1, $0, end2 # branch if > $a1
	sll $t1, $t0, 2 # mult by 4
	addu $t1, $t1, $t2 # get address
	lw $t1, 0($t1) # get word
	addi $v0, $0, 1 # set command to print int
	addi $a0, $t1, 0 # set value to print
	syscall # print int
	addi $a0, $t3, 12 # set address of newLine in $a0
	ori $v0, $0, 4 # set command to print string
	syscall # print string
	addi $t0, $t0, 1 # index it
	j top3 # jump to top3
end2:
	# print average
	addi $a0, $t3, 0x20 # address of array
	addi $a1, $t0, 0 # count
	addi $sp, $sp, -12 # allocate memory into stack
	sw $a0, 0($sp) # store $a0 in first location
	sw $a1, 4($sp) # store $a1 in second location
	sw $ra, 8($sp) # store $ra in third location
	jal average # call average
	lw $a0, 0($sp) # load word into $a0
	lw $a1, 4($sp) # load word into $a1
	lw $ra, 8($sp) # load word into $ra 
	addi $sp, $sp, 12 # decrement the stack back to original size
	addi $v0, $0, 2 # set command to print float 
	add.s $f12, $f12, $f0 # store value to print into $f12
	syscall # print float
	j final # jump to final
final:
	jr $ra # return register address
