      .data
x:    .word     9
y:    .word    -1

      .text
      .align    2
      .globl  main

main:
      la    $t0, x
      la    $t1, y
      lw    $t2, 0($t0)
      lw    $t3, 0($t1)

      add   $s0, $t2, $t3
      sub   $s1, $t2, $t3

      jr    $ra
