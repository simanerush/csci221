# Serafima Nerush
.data
arr:    .word 1, 2, 3, 5, 7, 9
size:   .word     6
.text
.align	2
.globl  main

numEvens:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li $v0, 0
loopTop:
  beq $a1, $0, loopEnd # if size is 0, end loop
  lw $t0, 0($a0) # load the first digit to t0
  andi $t0, 1 # AND the digit with 1
  bne $t0, $0, isOdd # if the result is not 0, then the digit is odd
  addi $v0, 1 # add 1 to the counter of evens
isOdd:
  addi $a0, 4 # move to next digit
  addi $a1, -1 # decrease the size by 1
  j loopTop # redo loop
loopEnd:
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

main:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  la $a0, arr # load array to a0
  la $t0, size # load the pointer to the size to t0
  lw $a1, 0($t0) # load the actual size value to a1
  jal numEvens # call the function
  move $a0, $v0 # move the output to a0
  li $v0, 1 # print the output
  syscall
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
