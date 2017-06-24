.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__C: .fill 2400,1,0
.data
	.__PC: .quad 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__C, %rax
	movq	%rax, .__PC
	movq	$1, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$3, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r10
	popq	%rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__C, %rax
	movq	$9, %rcx
	imulq	$24, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	$16, %rcx
	popq	(%rax,%rcx,1)
	movq	$100, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	movq	$3, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %r10
	popq	%rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	$9, %rcx
	imulq	$24, %rcx
	pushq	%rax
	movq	.__PC, %rax
	leaq	(%rax,%rcx,1), %rax
	movq	$8, %rcx
	popq	(%rax,%rcx,1)
	movq	$9, %rcx
	imulq	$24, %rcx
	movq	.__PC, %rax
	leaq	(%rax,%rcx,1), %rax
	movq	%rax, %r11
	movq	$16, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_float_, %rdi
	movq	%r11, %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__C, %rax
	movq	$9, %rcx
	imulq	$24, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	%rax, %r11
	movq	$8, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_float_, %rdi
	movq	%r11, %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

