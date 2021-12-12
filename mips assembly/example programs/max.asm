          .data

      .text
      .align    2
      .globl  main

# max: compute the larger value of two integers
my_max:
      addiu $sp, $sp, -4        # Grow stack
      sw    $ra, 0($sp)         # Save return address

      bge   $a0, $a1, first_num # If $a0 >= $a1, set return to $a0
      move  $v0, $a1            # Otherwise, set return value to $a1
      b     done_with_max

first_num:
      move  $v0, $a0            # Return the first parameter

done_with_max:
      lw    $ra, 0($sp)         # Restore $ra and $sp
      addiu $sp, $sp, 4
      jr    $ra

main:
      addiu $sp, $sp, -4        # Grow stack
      sw    $ra, 0($sp)         # Save return address

      li    $v0, 5              # Read an int from the user
      syscall
      move  $a0, $v0            # Copy it to input parameter #1
      li    $v0, 5              # Read an int from the user
      syscall
      move  $a1, $v0            # Copy it to input parameter #2

      jal   my_max

      move  $a0, $v0            # Move max' output to print's input
      li    $v0, 1              # Print the value
      syscall

      lw    $ra, 0($sp)         # Restore $ra and $sp
      addiu $sp, $sp, 4
      jr    $ra                 # main() is a function too!

# Can you guess the bug in the above code? Can you fix it?
