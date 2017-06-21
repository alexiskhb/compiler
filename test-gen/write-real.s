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
	pushq	$10
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	movq	$5.500000, %rax
	pushq	%rax
	leaq	.__B, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$9
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$1.400000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm0
	cvtsd2si	%xmm0, %rax
	pushq	%rax
	leaq	.__C, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	movq	$100.000000, %rax
	pushq	%rax
	popq	%rax
	movq	%rax, %xmm1
	xorpd	%xmm0, %xmm0
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__D, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// start block
	pushq	.__A
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	.__B
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	.__C
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$0.300000, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	.__D
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

