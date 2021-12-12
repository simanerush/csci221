          .data

      .text
      .align    2
      .globl  main

# abs: compute the absolute value of an integer
my_abs:
      li    $a1, 0
      bge   $a0, $a1, positive  # If the parameter is >= 0, nothing to do
      sub   $a0, $a1, $a0       # else, substract it from zero to negate.
positive:
      move  $v0, $a0            # Return the parameter (now assumed positive)
      jr    $ra

main:
      li    $v0, 5              # Read an int from the user
      syscall

      move  $a0, $v0            # Copy it to input parameter and call abs
      jal   my_abs

      move  $a0, $v0            # Move abs' output to print's input
      li    $v0, 1              # Print the value
      syscall

      jr    $ra                 # main() is a function too!

# Can you guess the bug in the above code? Can you fix it?
