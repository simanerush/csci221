# Serafima Nerush
.data
.text
.align	2
.globl  main

getsum:
  addiu $sp, -8 
  sw $ra, 0($sp)
  li $v0, 0   
  beq $a1, $0, cleanup # go to cleanup if the length is 0
  lw $v0, 0($a0)
  beq $a1, 1, cleanup # go to cleanup if the length is 1
  sw $a0, 4($sp)
  addi $a0, 4
  addi $a1, -1
  jal getsum
  lw $t0, 0($sp) # load $a0 from the heap
  lw $t1, 0($t0)
  add $v0, $t1, $v0

cleanup:
  lw $ra, 0($sp) # cleanup
  addiu $sp, 8
  jr    $ra


