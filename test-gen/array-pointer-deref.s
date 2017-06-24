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
	pushq	%rax
	leaq	.__PC, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	$3
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%r10
	popq	%rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__C, %rax
	pushq	%rax
	pushq	$0
	pushq	$10
	movq	$1, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$24, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	movq	$16, %rcx
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$100
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	$3
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	popq	%r10
	popq	%rax
	movq	%rax, %xmm0
	movq	%r10, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	pushq	.__PC
	pushq	$0
	pushq	$10
	movq	$1, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$24, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	movq	$8, %rcx
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__PC
	pushq	$0
	pushq	$10
	movq	$1, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$24, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%r11
	movq	$16, %r13
	movq	(%r11,%r13,1), %r11
	pushq	%r11
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__C, %rax
	pushq	%rax
	pushq	$0
	pushq	$10
	movq	$1, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$24, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%r11
	movq	$8, %r13
	movq	(%r11,%r13,1), %r11
	pushq	%r11
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

