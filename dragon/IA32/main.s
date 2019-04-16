	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$12, -4(%rbp)
	addl	$1, -4(%rbp)
	cmpl	$12, -4(%rbp)
	jle	.L2
	subl	$1, -4(%rbp)
.L2:
	movl	$1, %eax
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
