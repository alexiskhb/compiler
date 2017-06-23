.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__P: .fill 24,1,0
.data
	.__PP: .quad 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__P, %rax
	pushq	%rax
	leaq	.__PP, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// start block
	pushq	$1
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	$3
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$16, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$100
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	$3
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
	pushq	.__PP
	popq	%rax
	movq	$8, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// generate record start address
	pushq	.__PP
	popq	%rax
	movq	$16, %rbx
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$8, %rbx
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

