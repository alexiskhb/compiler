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
	.__B: .double 0
.data
	.__C: .quad 0
.data
	.__D: .double 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, .__A
	movq	$5.500000, %rax
	movq	%rax, .__B
	movq	$9, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	movq	$1.400000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	addsd	%xmm1, %xmm0
	cvtsd2si	%xmm0, %rax
	movq	%rax, .__C
	movq	$100.000000, %rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, .__D
	movq	.__A, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	movq	.__B, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	.__C, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r10
	popq	%rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	$0.300000, %r10
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	leaq	.__._fmt_float_, %rdi
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__._fmt_float_, %rdi
	movq	.__D, %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

