          .data
x:	  .word	    9
y:	  .word    -1

	  .text
	  .align	2
	  .globl  main

main:
	  la    $t0, x
	  lw	$t1, 0($t0)

	  sll	$t3, $t1, 2
	  sra   $t4, $t1, 2
	  srl   $t5, $t1, 2

	  la    $t0, y
	  lw	$t1, 0($t0)

	  sll	$t3, $t1, 2
	  sra   $t4, $t1, 2
	  srl   $t5, $t1, 2

	  jr	$ra