 #Serafima Nerush
    .text
    .align 2
    .globl main
main:
    li $v0, 5  #do input
    syscall
    move $t0, $v0 #store number of inputs in $t0
    li $t1, 0 #initialize an empty variable 0 in $t1
loop:
    blez $t0, done #if we have 0 inputs or negative we are done
    li $v0, 5 #set up the input
    syscall
    ble $v0, $t1, no_change #if th input is smaller than the previous, there is no change
    move $t1, $v0 #if it is bigger, store in $t1
no_change:
    addi $t0, -1 #decrease the number of input variables by 1
    j loop #reiterate loop
done:
  move $a0, $t1 #store the result in output register
  li $v0, 1 #set up output
  syscall
  jr $ra #quit main
