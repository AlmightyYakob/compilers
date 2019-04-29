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
moo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$303, %edi
	movl	%edi, -28(%ebp)
	movl	%edi, %eax
	addl	$12, %esp
	popl	%ebp
	ret
bar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$202, %edi
	pushl	%edi
	movl	%edi, %eax
	addl	$16, %esp
	popl	%ebp
	ret
boo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	$0, %edi
	movl	%edi, -28(%ebp)
	pushl	-28(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	$101, %edi
	pushl	%edi
	pushl	-28(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%edi, %eax
	addl	$36, %esp
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
