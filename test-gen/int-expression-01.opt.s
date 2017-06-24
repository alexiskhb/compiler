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
.__.str0:
	.string " "
.__.str1:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, .__A
	movq	$20, .__B
	movq	.__B, %r10
	addq	%r10, .__A
	leaq	.__._fmt_int_, %rdi
	movq	.__A, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rax
	subq	$40, %rax
	movq	%rax, .__B
	leaq	.__._fmt_int_, %rdi
	movq	.__A, %rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_int_, %rdi
	movq	.__B, %rsi
	call	printf
	leaq	.__.str1, %rdi
	call	printf
	movq	.__B, %r10
	movq	.__A, %rax
	addq	%r10, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

