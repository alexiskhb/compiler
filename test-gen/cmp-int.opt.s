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
	movq	.__A, %r10
	movq	.__A, %rax
	imulq	%r10, %rax
	addq	.__A, %rax
	movq	%rax, .__B
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$10, %rdx
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$10, %rdx
	setne	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$9, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$11, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$11, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	$9, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__B, %rdx
	xorq	%rax, %rax
	cmpq	$110, %rdx
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %r11
	movq	.__B, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__B, %r10
	movq	.__A, %rax
	addq	%r10, %rax
	movq	%rax, %r11
	movq	.__B, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %rax
	imulq	$100, %rax
	movq	%rax, %r11
	movq	.__B, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%r11, %r11
	movq	.__B, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$102, %rdx
	cmpq	$101, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$102, %rdx
	cmpq	$101, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$102, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$102, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$101, %rdx
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$102, %rdx
	cmpq	$101, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$102, %rdx
	cmpq	$101, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$102, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$102, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	movq	$101, %rdx
	cmpq	$101, %rdx
	setne	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__.str1, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$102, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$102, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$102, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$102, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setne	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$102, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setl	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$102, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$102, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$102, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setge	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$101, %rax
	negq	%rax
	pushq	%rax
	movq	$101, %rax
	negq	%rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

