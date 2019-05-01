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
	subl	$28, %esp
	movl	%ecx, -4(%ebp)
	leal	-16(%ebp), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	-16(%ebp), %edi
	movl	$50, %esi
	cmpl	%esi, %edi
	jl	.LC3
	movl	$1, %esi
	movl	%esi, -20(%ebp)
	jmp	.LC4
.LC3:
	movl	$0, %esi
	movl	%esi, -20(%ebp)
.LC4:
	pushl	-20(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%esi, %eax
	addl	$28, %esp
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
