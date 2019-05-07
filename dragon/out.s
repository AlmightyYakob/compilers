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
	subl	$52, %esp
	movl	%ecx, -4(%ebp)
	movl	$2, %edi
	movl	%ebp, %ecx
	movl	%edi, -36(%ecx)
	movl	$1, %edi
	movl	%ebp, %ecx
	movl	%edi, -40(%ecx)
	movl	$3, %edi
	movl	%ebp, %ecx
	movl	%edi, -44(%ecx)
	movl	%ebp, %ecx
	movl	-36(%ecx), %esi
	movl	%ebp, %ecx
	movl	-40(%ecx), %edi
	movl	%ebp, %ecx
	addl	-44(%ecx), %edi
	movl	%esi, %eax
	mul		%edi
	movl	%eax, %esi
	movl	%ebp, %ecx
	movl	-36(%ecx), %edi
	movl	%ebp, %ecx
	movl	-40(%ecx), %ebx
	movl	%ebp, %ecx
	addl	-44(%ecx), %ebx
	movl	%edi, %eax
	mul		%ebx
	movl	%eax, %edi
	addl	%esi, %edi
	movl	%edi, -12(%ebp)
	movl	%ebp, %ecx
	movl	-36(%ecx), %esi
	movl	%ebp, %ecx
	movl	-40(%ecx), %edi
	movl	%ebp, %ecx
	addl	-44(%ecx), %edi
	movl	%esi, %eax
	mul		%edi
	movl	%eax, %esi
	movl	%ebp, %ecx
	movl	-36(%ecx), %edi
	movl	%ebp, %ecx
	movl	-40(%ecx), %ebx
	movl	%ebp, %ecx
	addl	-44(%ecx), %ebx
	movl	%edi, %eax
	mul		%ebx
	movl	%eax, %edi
	addl	%esi, %edi
	movl	-12(%ebp), %esi
	movl	%esi, %eax
	mul		%edi
	movl	%eax, %esi
	movl	%ebp, %ecx
	movl	%esi, -24(%ecx)
	movl	%ebp, %ecx
	movl	-24(%ecx), %esi
	pushl	%esi
	pushl	$.LC0
	call	printf
	addl	$8, %esp
	addl	$52, %esp
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
