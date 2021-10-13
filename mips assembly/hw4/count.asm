# Serafima Nerush
  .data
str:    .asciiz "abcdefg"
.text
.align	2
.globl  main

countOccurences:
  addiu $sp, -4 # standard function setup
  sw $ra, 0($sp)
  li $v0, 0
loopTop:
  lb $t1, 0($a0) # load the first character of str to t1
  beq $t1, $0, loopEnd # end the loop if the string ends
  bne $t1, $a1, notEqual # check if the current character is equal to the desired one
  addi $v0, 1 # increase the counter if it is
notEqual:
  addi $a0, 1 # move to the next character
  j loopTop # redo loop
loopEnd:
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

main:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li    $v0, 12 # read a character from a user
  syscall
  move   $a1, $v0 # move the input to a1
  la     $a0, str # load the string to a0
  jal countOccurences # call the function on a0 and a1
  move $a0, $v0 # move the output to a0
  li $v0, 1 # print the output
  syscall
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
