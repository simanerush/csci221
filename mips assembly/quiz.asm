  .data
x: .word 3
  .text
  .align 2
  .globl main

#idea (python)
#fib(n):
# if n <= 1:
#   return n
#else:
#  return fib(n-1) + fib(n-2)

fib:
  bgt   $a0, 1, recursion_step              # if a0 is bigger than 1, do the recursion step
  move  $v0, $a0                            # a is 0 or 1, so that is the answer, move it to the output register
  jr    $ra
  recursion_step:
    addiu $sp, -12                          # standard function setup
    sw    $ra, 0($sp)
    sw    $a0, 4($sp)                       # store the initial input in stack, so that it won't get overwriten
    addi  $a0, -1                           # get n - 1 value
    jal   fib                               # call the function on n - 1
    sw    $v0, 8($sp)                       # store the output in the stack, to access it later
    lw    $a0, 4($sp)                       # load hte initial input we saved earlier
    addi  $a0, -2                           # get n - 2 value
    jal   fib                               # call the function on n - 2
    lw    $t3, 8($sp)                       # load the ouptut of fib(n - 1) from the stack
    add   $v0, $v0, $t3                     # add both values
    lw    $ra, 0($sp)                       # function cleanup
    addiu $sp, 12
    jr    $ra


main:
  addiu $sp, -4                             # standard function setup
  sw    $ra, 0($sp)
  lw    $a0, x
  jal   fib                                 # call fib(3)
  move  $a0, $v0
  li    $v0, 1
  syscall
  lw    $ra, 0($sp)                         # function cleanup
  addiu $sp, 4
  jr    $ra
