.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .fill 192,1,0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__A, %rax
	pushq	$415
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	$416
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$6, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	pushq	%r10
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	pushq	%r10
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$2, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	pushq	%r10
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$6, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$2, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	pushq	%rax
	movq	$1, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$6, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	pushq	%rax
	xorq	%rax, %rax
	subq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	leaq	.__A, %rax
	pushq	%rax
	movq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	movq	$5, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	movq	%rax, %r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__A, %rax
	pushq	%rax
	xorq	%rax, %rax
	subq	$2, %rax
	imulq	$6, %rax
	movq	$1, %r9
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	imulq	$4, %rax
	popq	%r9
	addq	%r9, %rax
	movq	$3, %r9
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	movq	%rax, %r10
	popq	%rax
	subq	%r10, %rax
	addq	$8, %rax
	leaq	.__._fmt_int_, %rdi
	movq	(%rax), %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

