# This program read in two positive integers, a and b, from the user and
# prints a * b.
#Serafima Nerush
    .text
    .align 2
    .globl main
main:
    li   $v0, 5          # set up reading of first int
    syscall
    move $t0, $v0        # store first int, a, into $t0
    blt  $t0, $0, done   # go to done if a not positive

    li   $v0, 5          # set up reading of second int
    syscall
    move $t1, $v0        # store second int, b, into $t1
    blt  $t1, $0, done   # go to done if b not positive

    move $v0, $0        #clean $v0 register

    li $t2, 0          #store 0 in $t2, this is a counter
    li $a0, 0          #store 0 in $a0, because it will be used for printing

loop:
    beq  $t0, $t2, print #if counter is equal to the first integer, then we are done
    add  $a0, $a0, $t1  #add the value of the second integer to 0
    addi  $t2, $t2, 1   #counter increases
    b loop

print:
    li   $v0, 1       # set up "print int" system call
    syscall           # execute system call

done:
    jr   $ra          # return from main method
