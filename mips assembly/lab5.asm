      .data
x:    .word 1, 2, 3, 4
      .text
      .align	2
      .globl  main

isSingleBit:
addiu $sp, -4 # standard function setup
sw $ra, 0($sp)
li $t4, 0    # counter of 1's
li $t5, 1    # variable 1 for comparing with 1
li $t2, 1    # variable 1 for AND'ing
  loop:
    ble $a0, $0, return_val  # if input is 0, we are done
    srl $t1, $a0, 1          # shift right arithmetic by 1
    move $a0, $t1            # move the shifted value to $a0
    and $t3, $t2, $a0        # AND 1 with the shifted value
    beq $t3, $t5, has_one    # if shifted value is 1 after that, then we have at least one 1 in the digit
    j loop                   # loop again
  has_one:
    addi  $t4, $t4, 1        # if has one, add 1 to the counter
    j loop                   # loop again


  return_val:

    beq $t4, $t5, return_true   # return true or false

    return_false:
      li $v0, 0                # return 0
      lw $ra, 0($sp)           # function cleanup
      addiu $sp, 4
      jr $ra
    return_true:
      li $v0, 1                # return 1
      lw $ra, 0($sp)           # function cleanup
      lw $ra, 0($sp)
      addiu $sp, 4
      jr $ra

sumArray:
  addiu $sp, -4                # standard function setup
  sw $ra, 0($sp)
  li $t0, 0                    # sum variable
  li $t1, 0                    # i variable
  array_loop:
  bge $t1, $a1, done           # if we reach the array length, we are done
  lw $t2, 0($a0)               # load the first thing in array
  add    $t0, $t0, $t2         # add it to sum
  addi   $a0, 4                # move pointer to the next thing in array
  addi  $t1, $t1, 1            # increase i
  j array_loop                 # redo loop

  done:
  move $v0, $t0                # if done, move sum to output
  lw $ra, 0($sp)               # function cleanup
  addiu $sp, 4
  jr $ra

recSumArray:
  addiu $sp, -8               # function setup: allocate 8 stack bytes
  sw $ra, 0($sp)
  li $v0, 0
  beq    $a1, $0, done_recursion  # base case, length is 0
  lw     $t0, 0($a0)              # load next word
  addi  $a0, 4                    # move the pointer to the next word
  addi  $a1, -1                   # decrease the length of the array
  sw    $t0, 4($sp)               # save the current word to the stack
  jal recSumArray                 # call the function
  lw     $t0, 4($sp)              # load the previous word from the stack
  add    $t1, $v0, $t0            # add this word to the sum
  move   $v0, $t1                 # output the sum

  done_recursion:
    lw $ra, 0($sp)               # clean the stack
    addiu $sp, 8
    jr $ra

main:
  jr $ra
