# Serafima Nerush
.data
.text
.align	2
.globl  main

recpow:
  addiu $sp, -8 # setup function
  sw $ra, 0($sp)
  li $v0, 1 # base case: the power is 0, output is 1
  beq $a1, $0, cleanup # go to cleanup if the power is 0
  sw $a0, 4($sp) # save the previous value in stack
  addi $a1, -1 # decrease the power by 1
  jal recpow # call the function
  lw $a0, 4($sp) # load the value from the stack
  mult $v0, $a0 # multiply v0 by a0
  mflo $v0 # get v0 from the LO
cleanup:
  lw $ra, 0($sp) # cleanup
  addiu $sp, 8
  jr    $ra

main:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li $v0, 5 # get user's input
  syscall
  move $s0, $v0 # move the input to s0
  li $v0, 5 # get the input
  syscall
  move $a0, $s0 # move it to the a0, because syscall could have overwriten a0
  move $a1, $v0 # move our second input to a1
  jal recpow # call the function
  move $a0, $v0 # move the output to a0
  li $v0, 1 # print the output
  syscall
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
