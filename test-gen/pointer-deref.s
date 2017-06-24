.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .quad 0
.data
	.__P: .quad 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	$20
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	leaq	.__A, %rax
	pushq	%rax
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__P
	popq	%rax
	pushq	(%rax)
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

