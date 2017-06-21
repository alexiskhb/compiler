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
// start block
	pushq	$100
	pushq	$200
	popq	%rbx
	popq	%rax
	subq	%rbx, %rax
	pushq	%rax
	pushq	$10
	popq	%rbx
	popq	%rax
	cqo
	idivq	%rbx
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

