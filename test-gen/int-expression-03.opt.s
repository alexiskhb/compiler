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
	.__C: .quad 0
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
	movq	.__A, %rax
	imulq	%r10, %rax
	movq	.__B, %r10
	pushq	%rax
	movq	.__A, %rax
	subq	%r10, %rax
	movq	%rax, %r10
	popq	%rax
	addq	%r10, %rax
	movq	.__A, %r10
	pushq	%rax
	movq	.__B, %rax
	cqo
	idivq	%r10
	movq	%rax, %r10
	popq	%rax
	addq	%r10, %rax
	movq	%rax, .__C
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
	leaq	.__._fmt_int_, %rdi
	movq	.__C, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$1234, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$10, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$13, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$7, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$13, %rax
	negq	%rax
	xorq	%rdx, %rdx
	cqo
	movq	$7, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

