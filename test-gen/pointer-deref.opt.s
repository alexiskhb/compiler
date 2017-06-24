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
	movq	$20, .__A
	leaq	.__A, %rax
	movq	%rax, .__P
	movq	.__P, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

