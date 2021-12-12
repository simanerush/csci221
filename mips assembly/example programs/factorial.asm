      .data

      .text
      .align    2
      .globl  main


# Factorial: a recursive factorial function
# Expects its positive argument in $a0, returns in $v0
# This example uses $fp for convenient access to the local $a0 variable
factorial:
    sw    $fp, -4($sp)    # Save $fp in the stack
    move  $fp, $sp        # Set the frame pointer to start at current $sp
    sw    $a0, -8($fp)    # Save $a0 in the stack
    addiu $sp, $sp, -12   # make room in stack for $fp, $a0, and $ra
    sw    $ra, 0($sp)     # Save $ra in the new stack location

    li $t1, 1             # If $a0 < 1, return 1 and be done
    blt $a0, $t1, case_one

recursive_case:           # Otherwise, compute $a0 * factorial($a0-1):
    addiu $a0, $a0, -1
    jal   factorial
    lw    $a0, -8($fp)    # Restore the original $a0 after recursion
    mul   $v0, $a0, $v0
    j done_factorial

case_one:
  li $v0, 1

done_factorial:
    lw    $ra, 0($sp)     # Restore ra
    lw    $a0, -8($fp)    # Restore the original $a0 after recursion
    addiu $sp, $sp, 12    # Restore $sp
    lw    $fp, -4($sp)    # Restore fp
    jr $ra

# Get input from user, compute factorial and print
main:
      addiu $sp, $sp, -4        # Grow stack
      sw    $ra, 0($sp)         # Save return address

      li    $v0, 5              # Read an int from the user
      syscall
      move  $a0, $v0            # Copy it to input parameter #1

      jal   factorial

      move  $a0, $v0            # Move factorial's output to print's input
      li    $v0, 1              # Print the value
      syscall

      lw    $ra, 0($sp)         # Restore $ra and $sp
      addiu $sp, $sp, 4
      jr    $ra                 # main() is a function too!


