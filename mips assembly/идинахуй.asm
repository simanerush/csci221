  .text
  .align 2
  .globl main

isPrime:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  blt $a0, 2, done
  li $t0, 2
loop:

  bge $t0, $a0, done1
  div    $a0, $t0
  mfhi  $t3
  beq $t3, $0, done
  addiu $t0, 1
  j loop
done:
  li $v0, 0
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
done1:
  li $v0, 1
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

isPrimeRec2:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  beq $a1, $a0, done_recursion1
  div $a0, $a1
  mfhi $t3
  beq $t3, $0, done_recursion0
  addi  $a1, $a1, 1
  jal isPrimeRec2
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
done_recursion0:
  li $v0, 0
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
done_recursion1:
  li $v0, 1
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

isPrimeRec:
addiu $sp, -4 # function setup
sw $ra, 0($sp)
  li $a1, 2
  jal isPrimeRec2
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

primeFactors:
  addiu $sp, -12 # function setup
  sw $ra, 0($sp)
  blt $a0, 2, done
  li $t0, 2
  patricks_loop:

  bge $t0, $a0, done_factor
  sw $a0, 4($sp)
  sw $t0, 8($sp)
  move $a0, $t0
  jal isPrime
  lw $a0, 4($sp)
  lw $t0, 8($sp)
  beq $v0, $0, not_prime
is_prime:
  div   $a0, $t0
  mfhi $t6
  bne $t6, $0, not_prime
  sw $a0, 4($sp)
  move   $a0, $t0
  li    $v0, 1
  syscall
  li $a0, 10
  li $v0, 12
  syscall
  lw $a0, 4($sp)
  not_prime:
  addiu $t0, 1
  j patricks_loop
  done_factor:
  li $v0, 0
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 12
  jr    $ra


main:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li $v0, 5
  syscall
  move $a0, $v0
  jal primeFactors

  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
