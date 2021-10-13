#Serafima Nerush
    .data
    .text
    .align 2
    .globl main

main:
    addi $sp, $sp, -4   # grow the stack
    sw $ra, 0($sp)      # store the return address onto the stack
    li $v0, 5
    syscall             #get user input x
    move $t2, $v0       #store input in $t2
    li $v0, 5
    syscall            #get second input y
    move $t3, $v0      #store y in $t3
    bge $t3, $t2, is_bigger2 #check if y is bigger than x
    is_bigger1:           # executes if x is bigger than y
      move $a0, $t2       # move the value of t2(x) to a0
      li $v0, 1           # set up "print int" system call
      syscall             # execute system call
      j end               #jump to end because we don't want the second condition to also execute


    is_bigger2:           #executes if y is bigger than x
      move $a0, $t3       # move the value of t3(y) to a0
      li $v0, 1           # set up "print int" system call
      syscall             # execute system call

end:
    lw $ra, 0($sp)      # get the return address from the stack
    addi $sp, $sp, 4    # shrink the stack
    jr $ra              # return from main method
