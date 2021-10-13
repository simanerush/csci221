#Serafima Nerush
    .text
    .align 2
    .globl main
main:
    li $v0, 5        #set up input
    syscall
    move $t0, $v0   #store the input in $t0
    ble $t0, $0, done #if the value is smaller or equal to 0, exit
    li $t1, 0  #set up counter
loop:
    beqz $t0, done  #if the input becomes 0, exit
    add $t1, $t1, $t0 #add input to counter value
    addi $t0, -1 #substract 1 from the input at every iteration
    j loop #re-do loop

done:
    move $a0, $t1 #move the result to the output register
    li $v0, 1 #set up output
    syscall
    jr   $ra          # return from main method
