.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.__.str0:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$2, %rax
	imulq	$2, %rax
	movq	%rax, %r10
	movq	$2, %rax
	addq	%r10, %rax
	movq	$3, %r10
	pushq	%rax
	movq	$3, %rax
	addq	%r10, %rax
	movq	%rax, %r10
	popq	%rax
	subq	%r10, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	movq	$10, %rax
	cqo
	movq	$2, %r10
	idivq	%r10
	imulq	$3, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

