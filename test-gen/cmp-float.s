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
	pushq	$10
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__A
	pushq	.__A
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	.__A
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__B, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// start block
	pushq	.__A
	pushq	$10
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
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
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
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
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$11
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$11
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__A
	pushq	$9
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	$110
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
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
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
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
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	.__A
	pushq	$100
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__B
	pushq	$0
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
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
	movq	$10.200000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	sete	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
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
	pushq	$0
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	$0
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setne	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setb	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setbe	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	seta	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.200000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
	movq	$0, %rax
	setae	%al
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$10.100000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	comisd	%xmm1, %xmm0
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

