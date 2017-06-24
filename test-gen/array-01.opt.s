.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .fill 808,1,0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	$20
	pushq	%rax
	movq	$10, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	%rax
	movq	$10, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	pushq	%r10
	movq	$10, %r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	$9, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	$9, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	$10, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

