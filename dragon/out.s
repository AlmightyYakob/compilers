	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$10, %esp
	movl	%edi, %eax
	popl	%ebp
	ret
