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
	subl	$116, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	movl	8(%ecx), %eax
	movl	%eax, -12(%ecx)
	movl	%ebp, %ecx
	movl	12(%ecx), %eax
	movl	%eax, -12(%ecx)
	movl	%ebp, %ecx
	leal	-24(%ecx), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	$0, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
	jmp	.LC3
.LC4:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-28(%ecx), %eax
	mul		%edi
	movl	%eax, %edi
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	movl	$4, %eax
	mul		%esi
	addl	$32, %eax
	movl	%ebp, %ecx
	subl	%eax, %ecx
	movl	%edi, (%ecx)
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	addl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
.LC3:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-24(%ecx), %esi
	cmp		%esi, %edi
	jle	.LC4
	movl	$0, %esi
	movl	%ebp, %ecx
	movl	%esi, -28(%ecx)
	jmp	.LC5
.LC6:
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	movl	$4, %eax
	mul		%esi
	addl	$32, %eax
	movl	%ebp, %ecx
	subl	%eax, %ecx
	pushl	(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	addl	$1, %esi
	movl	%ebp, %ecx
	movl	%esi, -28(%ecx)
.LC5:
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	movl	%ebp, %ecx
	movl	-24(%ecx), %ebx
	cmp		%ebx, %esi
	jle	.LC6
	addl	$116, %esp
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
