      .data

      .text
      .align    2
      .globl  main

# pow: compute the exponentiation of $a0 to the power of $a1
my_pow:
      move  $fp, $sp
      li    $t0, 1              # Store result in local variable
      sw    $t0, -4($fp)
      li    $t0, 0              # Store i in local variable
      sw    $t0, -8($fp)

      addiu $sp, $sp, -12       # Grow stack: two locals and one return address
      sw    $ra, 0($sp)         # Save return address

pow_loop:
      lw    $t0, -8($fp)        # Compare i to exponent:
      bge   $t0, $a1, done_loop # If i >= exponent, we're done

      lw    $t0, -4($fp)        # Load result and multiply by base
      mul   $t0, $t0, $a0
      sw    $t0, -4($fp)

      lw    $t0, -8($fp)        # Increment i
      addi  $t0, $t0, 1
      sw    $t0, -8($fp)

      b     pow_loop            # Strt next iteration

done_loop:
      lw    $v0, -4($fp)        # Return result in $v0
      lw    $ra, 0($sp)         # Restore $ra and $sp
      addiu $sp, $sp, 12
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

      jal   my_pow

      move  $a0, $v0            # Move max' output to print's input
      li    $v0, 1              # Print the value
      syscall

      lw    $ra, 0($sp)         # Restore $ra and $sp
      addiu $sp, $sp, 4
      jr    $ra                 # main() is a function too!

# Can you guess the bug in the above code? Can you fix it?
