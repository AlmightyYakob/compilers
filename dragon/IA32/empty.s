	.file	"empty.c"
	.text
	.globl	actual
	.type	actual, @function
actual:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$1, -16(%ebp)
	movl	$2, -12(%ebp)
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-16(%ebp), %edx
	movl	-8(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	actual, .-actual
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	call	actual
	movl	$0, %eax
	popl	%ebp
	ret
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
	movl	(%esp), %eax
	ret
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
