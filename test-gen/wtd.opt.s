.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$1.000000, %rax
	movq	$2.000000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	$100.000000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	leaq	.__._fmt_float_, %rdi
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$100.000000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	leaq	.__._fmt_float_, %rdi
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

