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
	pushq	$100
	pushq	$200
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	pushq	$10
	popq	%r10
	popq	%rax
	cqo
	idivq	%r10
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

