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
	subl	$24, %esp
	leal	-16(%ebp), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	-16(%ebp), %edi
	movl	-16(%ebp), %eax
	mul		%edi
	movl	%eax, %edi
	movl	$2, %esi
	movl	-16(%ebp), %eax
	mul		%esi
	movl	%eax, %esi
	subl	%esi, %edi
	addl	$1, %edi
	movl	%edi, -16(%ebp)
	pushl	-16(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%edi, %eax
	addl	$24, %esp
	popl	%ebp
	ret
main:
	pushl	%ebp
	movl	%esp, %ebp
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
