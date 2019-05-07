	.section	.rodata
.LC0:
	.string "%d\n"
.LC1:
	.string "%f\n"
.LC2:
	.string "%d"
	.text
	.globl	main
	.type	main, @function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	movl	8(%ecx), %eax
	movl	%eax, -16(%ecx)
	movl	%ebp, %ecx
	movl	-16(%ecx), %edi
	movl	%edi, %eax
	movl	$10, %edi
	movl	$0, %edx
	div		%edi
	movl	%eax, %edi
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	%edi, -32(%ecx)
	addl	$20, %esp
	popl	%ebp
	ret
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	leal	-24(%ecx), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	%ebp, %ecx
	pushl	-24(%ecx)
	movl	%ebp, %ecx
	call	foo
	addl	$4, %esp
	movl	%ebp, %ecx
	movl	-32(%ecx), %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	pushl	%edi
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	addl	$40, %esp
	popl	%ebp
	ret
main:
	pushl	%ebp
	movl	%esp, %ebp
	call	boo
	popl	%ebp
	ret
	.size   main, .-main
	.section    .text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl  __x86.get_pc_thunk.ax
	.hidden __x86.get_pc_thunk.ax
	.type   __x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
	movl    (%esp), %eax
	ret
	.ident  "GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section    .note.GNU-stack,"",@progbits
