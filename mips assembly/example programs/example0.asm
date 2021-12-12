
  .data
x:  .word 5

  .text
  .align 2
  .globl  main

main:
  la  $t0, x        # This is the first instruction of the program
  lw  $t1, 0($t0)
  addi  $t1, $t1, 2
  sw  $t1, 0($t0)
  jr  $ra
