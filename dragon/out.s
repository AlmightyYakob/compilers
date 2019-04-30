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
factorial:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%ecx, -4(%ebp)
	movl	-8(%ebp), %edi
	movl	$1, %esi
	cmpl	%esi, %edi
	jle	.LC3
	movl	-24(%ebp), %ebx
	movl	-8(%ebp), %esi
	subl	$1, %esi
	???	%esi, %ebx
	movl	-8(%ebp), %esi
	movl	%ebx, %eax
	mul		%esi
	movl	%eax, %esi
	movl	%esi, -24(%ebp)
	jmp	.LC4
.LC3:
	movl	$1, %esi
	movl	%esi, -24(%ebp)
.LC4:
	movl	%esi, %eax
	addl	$12, %esp
	popl	%ebp
	ret
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	movl	%ecx, -4(%ebp)
	leal	-20(%ebp), %esi
	pushl	%esi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	-24(%ebp), %esi
	???	-20(%ebp), %esi
	movl	%esi, -16(%ebp)
	pushl	-16(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%esi, %eax
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
