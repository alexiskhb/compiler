.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .double 0
.data
	.__B: .double 0
.__.str0:
	.string " "
.__.str1:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	movq	%rax, .__A
	movq	.__A, %r10
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	.__A, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, .__B
	movq	$10, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setne	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$9, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$11, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$11, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$9, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$110, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__B, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__A, %r11
	movq	.__B, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	.__B, %r10
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	movq	.__B, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$100, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r10
	movq	.__A, %rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	movq	.__B, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r11
	movq	.__B, %rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.200000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.200000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.200000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.200000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	$10.100000, %r11
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
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
	xorq	%rax, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	movq	$10.200000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	xorq	%rax, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	movq	$10.100000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setne	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setb	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setbe	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	seta	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	setae	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %r11
	popq	%rax
	movq	%rax, %xmm0
	movq	%r11, %xmm1
	xorq	%rax, %rax
	comisd	%xmm1, %xmm0
	sete	%al
	leaq	.__._fmt_int_, %rdi
	movq	%rax, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

