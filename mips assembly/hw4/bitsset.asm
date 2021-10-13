# Serafima Nerush
.data
.text
.align	2
.globl  main

bitsset:
  addiu $sp, -8 # function setup - allocate more stack space to save stuff
  sw $ra, 0($sp)
  li $v0, 0 # set the counter to 0
  beq $a0, $0, cleanup # if the input is 0, we are done
  andi $t0, $a0, 1 # AND the input with 1
  sw $t0, 4($sp) # store the result in stack
  srl $a0, $a0, 1 # shift a0 left
  jal bitsset # call the function
  lw $t0, 4($sp) # load the previous t0 value from the stack
  add $v0, $v0, $t0 # t0 can be either 1 or 0, so add it to a counter
cleanup:
  lw $ra, 0($sp) # cleanup
  addiu $sp, 8
  jr    $ra

main:
addiu $sp, -4 # function setup
sw $ra, 0($sp)
li $v0, 5 # set up input
syscall
move $a0, $v0 # move input to a0
jal bitsset # call the function
move $a0, $v0 # move the output to a0
li $v0, 1 # print the outpur
syscall
lw $ra, 0($sp) # cleanup
addiu $sp, 4
jr    $ra
