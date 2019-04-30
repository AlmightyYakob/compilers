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
	subl	$44, %esp
	leal	-20(%ebp), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	leal	-24(%ebp), %edi
	pushl	%edi
	pushl	$.LC2
	call	scanf
	addl	$8, %esp
	movl	$3, %esi
	movl	-24(%ebp), %edi
	movl	%edi, %eax
	movl	$3, %edi
	movl	$0, %edx
	div		%edi
	movl	%edx, %edi
	movl	%esi, %eax
	mul		%edi
	movl	%eax, %esi
	addl	$5, %esi
	movl	-20(%ebp), %edi
	movl	%edi, %eax
	movl	%esi, %edi
	movl	$0, %edx
	div		%edi
	movl	%eax, %edi
	movl	%edi, -28(%ebp)
	pushl	-28(%ebp)
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	movl	%edi, %eax
	addl	$44, %esp
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
