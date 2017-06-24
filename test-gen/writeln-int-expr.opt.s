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
	movq	$-100, %rax
	cqo
	movq	$10, %r10
	idivq	%r10
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

