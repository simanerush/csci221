  .data
  str:    .space 21

    .text
    .align 2
    .globl main


isLowerCase:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li $t1, 97
  li $t2, 122
  blt $a0, $t1, false
  bgt $a0, $t2, false
  true:
  li $v0, 1
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
  false:
  li $v0, 0
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

getUpperCase:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  li $t1, 97
  li $t2, 122
  blt $a0, $t1, false2
  bgt $a0, $t2, false2
  true2:
  addi  $a0, $a0, -32
  move $v0, $a0
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra
  false2:
  li $v0, 48
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr    $ra

convertString:
  addiu $sp, -12 # function setup
  sw $ra, 0($sp)
  sw $a0, 8($sp)
loopTop:
  lb $t1, 0($a0) # load the first character of str to t1
  sw $a0, 4($sp)
  beq $t1, $0, loopEnd # end the loop if the string ends
  move $a0, $t1
  jal isLowerCase
  move $t2, $v0
  li $t3, 1
  beq $t2, $t3, is_lower_case
is_upper_case:
  lw $a0, 4($sp)
  addi $a0, 1
  j loopTop
is_lower_case:
  jal getUpperCase
  lw $a0, 4($sp)
  sb $v0, 0($a0)
  addi $a0, 1
  j loopTop

loopEnd:
  lw $v0, 8($sp)
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 12
  jr    $ra

main:
  addiu $sp, -4 # function setup
  sw $ra, 0($sp)
  la  $a0, str # load the string to a0
  li $a1, 21
  li $v0, 8
  syscall
  jal convertString
  move $a0, $v0
  li $v0, 4
  syscall
  lw $ra, 0($sp) # function cleanup
  addiu $sp, 4
  jr $ra
