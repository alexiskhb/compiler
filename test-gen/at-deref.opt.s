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
	.__B: .quad 0
.data
	.__C: .double 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, .__A
	movq	$20, .__B
	movq	$5.500000, %rax
	movq	%rax, .__C
	leaq	.__A, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	addq	$8, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__B, %rax
	subq	$8, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__C, %rax
	leaq	.__._fmt_float_, %rdi
	movq	(%rax), %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__B, %rax
	addq	$8, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

