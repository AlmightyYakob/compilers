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
gcd:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	movl	8(%ecx), %eax
	movl	%eax, -16(%ecx)
	movl	%ebp, %ecx
	movl	12(%ecx), %eax
	movl	%eax, -12(%ecx)
	movl	%ebp, %ecx
	pushl	-12(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%ebp, %ecx
	pushl	-16(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	pushl	$99
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-16(%ecx), %edi
	movl	$0, %esi
	cmp		%esi, %edi
	je	.LC3
	movl	%ebp, %ecx
	movl	-12(%ecx), %esi
	movl	%esi, %eax
	movl	%ebp, %ecx
	movl	-16(%ecx), %esi
	movl	$0, %edx
	div		%esi
	movl	%edx, %esi
	pushl	%esi
	movl	%ebp, %ecx
	pushl	-16(%ecx)
	movl	-4(%ebp), %ecx
	call	gcd
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	-28(%ecx), %esi
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	%esi, -28(%ecx)
	jmp	.LC4
.LC3:
	movl	%ebp, %ecx
	movl	-12(%ecx), %esi
	movl	%ebp, %ecx
	movl	-4(%ecx), %ecx
	movl	%esi, -28(%ecx)
.LC4:
	addl	$20, %esp
	popl	%ebp
	ret
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -4(%ebp)
	movl	%ebp, %ecx
	movl	8(%ecx), %eax
	movl	%eax, -8(%ecx)
	movl	%ebp, %ecx
	movl	12(%ecx), %eax
	movl	%eax, -8(%ecx)
	movl	%ebp, %ecx
	leal	-20(%ecx), %esi
	pushl	%esi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	%ebp, %ecx
	leal	-24(%ecx), %esi
	pushl	%esi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	%ebp, %ecx
	pushl	-24(%ecx)
	movl	%ebp, %ecx
	pushl	-20(%ecx)
	movl	%ebp, %ecx
	call	gcd
	addl	$8, %esp
	movl	%ebp, %ecx
	movl	-28(%ecx), %esi
	movl	%ebp, %ecx
	movl	%esi, -20(%ecx)
	movl	%ebp, %ecx
	pushl	-20(%ecx)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	addl	$36, %esp
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
