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
	pushq	$10
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__A
	pushq	.__A
	popq	%rbx
	popq	%rax
	imulq	%rbx, %rax
	pushq	%rax
	pushq	.__A
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__B, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// start block
	pushq	.__A
	pushq	$10
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	sete	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$10
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$9
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$11
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$11
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$9
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	$110
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	sete	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	.__A
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	.__A
	pushq	.__B
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	.__A
	pushq	$100
	popq	%rbx
	popq	%rax
	imulq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	$0
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$102
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$102
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	sete	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$102
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$102
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	pushq	$101
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__.str1, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setl	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setle	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setg	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$102
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setge	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	pushq	$101
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	sete	%al
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

