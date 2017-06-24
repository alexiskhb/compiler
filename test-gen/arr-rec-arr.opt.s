.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__CURVE: .fill 1600,1,0
.data
	.__DCURVE: .fill 3200,1,0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__CURVE, %rax
	movq	$9, %rcx
	imulq	$16, %rcx
	leaq	(%rax,%rcx,1), %rax
	xorq	%rcx, %rcx
	popq	(%rax,%rcx,1)
	movq	$20, %rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__DCURVE, %rax
	movq	$1600, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	$19, %rcx
	imulq	$16, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	$8, %rcx
	popq	(%rax,%rcx,1)
	leaq	.__CURVE, %rax
	movq	$9, %rcx
	imulq	$16, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	%rax, %r11
	xorq	%r13, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_float_, %rdi
	movq	%r11, %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__DCURVE, %rax
	movq	$1600, %rcx
	leaq	(%rax,%rcx,1), %rax
	movq	$19, %rcx
	imulq	$16, %rcx
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

