      .data
str:    .asciiz   "Inconceivable!"

      .text
      .align 2
      .globl main


strlen:
    move    $t0, $a0        # Copy argument to a new temporary
    li      $v0, 0          # Return value: string length
    li      $t1, 0          # Constant zero for comparison

lenloop:
    lb      $t2, 0($t0)     # Read next byte
    beq     $t2, $t1, done
    addiu   $v0, $v0, 1     # This byte isn't zero, increase length
    addiu   $t0, $t0, 1     # Increment str pointer
    b       lenloop

done:
    jr      $ra


main:
    addiu $sp, $sp, -4        # Grow stack
    sw    $ra, 0($sp)         # Save return address

    la    $a0, str
    jal   strlen
    move  $a0, $v0
    li    $v0, 1
    syscall

    lw    $ra, 0($sp)         # Restore $ra and $sp
    addiu $sp, $sp, 4
    jr    $ra                 # main() is a function too!
