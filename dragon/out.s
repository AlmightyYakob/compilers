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
	movl	$1, %esi
	cmp		%esi, %edi
	jle	.LC3
	movl	%ebp, %ecx
	movl	-16(%ecx), %edi
	subl	$1, %edi
	pushl	%edi
	movl	-4(%ebp), %ecx
	call	foo
	addl	$4, %esp
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	-72(%ecx), %edi
	movl	%ebp, %ecx
	movl	-16(%ecx), %eax
	mul		%edi
	movl	%eax, %edi
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	%edi, -72(%ecx)
	jmp	.LC4
.LC3:
	movl	$1, %edi
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	%edi, -72(%ecx)
.LC4:
	addl	$20, %esp
	popl	%ebp
	ret
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$80, %esp
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
	movl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
	jmp	.LC5
.LC6:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	subl	$1, %esi
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
.LC5:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-24(%ecx), %esi
	cmp		%esi, %edi
	jle	.LC6
	movl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
	jmp	.LC7
.LC8:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	subl	$1, %edi
	movl	$4, %eax
	mul		%edi
	addl	$32, %eax
	movl	%ebp, %ecx
	subl	%eax, %ecx
	movl	(%ecx), %edi
	addl	$1, %edi
	pushl	%edi
	movl	%ebp, %ecx
	call	foo
	addl	$4, %esp
	movl	%ebp, %ecx
	movl	-72(%ecx), %edi
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	subl	$1, %esi
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
.LC7:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-24(%ecx), %esi
	cmp		%esi, %edi
	jle	.LC8
	movl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
	jmp	.LC9
.LC10:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	subl	$1, %edi
	movl	$4, %eax
	mul		%edi
	addl	$32, %eax
	movl	%ebp, %ecx
	subl	%eax, %ecx
	pushl	(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	addl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -28(%ecx)
.LC9:
	movl	%ebp, %ecx
	movl	-28(%ecx), %edi
	movl	%ebp, %ecx
	movl	-24(%ecx), %esi
	cmp		%esi, %edi
	jle	.LC10
	addl	$80, %esp
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
