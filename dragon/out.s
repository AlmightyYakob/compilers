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
	subl	$40, %esp
	movl	%ecx, -4(%ebp)
	movl	$1078523331, %edi
	movl	%ebp, %ecx
	movl	%edi, -24(%ecx)
	movl	%ebp, %ecx
	movl	-24(%ecx), %edi
	pushl	%edi
	pushl	$.LC1
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
