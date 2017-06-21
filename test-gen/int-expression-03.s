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
// start block
	pushq	$10
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$20
	leaq	.__B, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__A
	pushq	.__B
	popq	%rbx
	popq	%rax
	imulq	%rbx, %rax
	pushq	%rax
	pushq	.__A
	pushq	.__B
	popq	%rbx
	popq	%rax
	subq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	pushq	.__B
	pushq	.__A
	popq	%rbx
	popq	%rax
	cqo
	idivq	%rbx
	pushq	%rax
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__C, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__A
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	pushq	.__B
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__.str1, %rdi
	call	printf
	pushq	.__C
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

