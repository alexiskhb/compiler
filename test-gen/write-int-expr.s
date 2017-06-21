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
// start block
	pushq	$2
	pushq	$2
	pushq	$2
	popq	%rbx
	popq	%rax
	imulq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	pushq	$3
	pushq	$3
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	subq	%rbx, %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	pushq	$10
	pushq	$2
	popq	%rbx
	popq	%rax
	cqo
	idivq	%rbx
	pushq	%rax
	pushq	$3
	popq	%rbx
	popq	%rax
	imulq	%rbx, %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

