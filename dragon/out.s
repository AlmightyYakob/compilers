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
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	leal	-16(%ecx), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	%ebp, %ecx
	leal	-20(%ecx), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-16(%ecx), %edi
	movl	%edi, %eax
	movl	%ebp, %ecx
	movl	-20(%ecx), %edi
	movl	$0, %edx
	div		%edi
	movl	%eax, %edi
	movl	%ebp, %ecx
	movl	%edi, -24(%ecx)
	movl	%ebp, %ecx
	pushl	-24(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%edi, %eax
	addl	$32, %esp
	popl	%ebp
	ret
main:
	pushl	%ebp
	movl	%esp, %ebp
	movl	%ecx, -4(%ebp)
	call	boo
	movl	$0, %eax
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
