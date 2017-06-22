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
// start block
	pushq	$10
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__CURVE, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$10
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$16, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$0, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$20
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
// generate record start address
	leaq	.__DCURVE, %rax
	pushq	%rax
	popq	%rax
	movq	$1600, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$20
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$16, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$8, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__CURVE, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$10
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$16, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$0, %rbx
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
// generate record start address
	leaq	.__DCURVE, %rax
	pushq	%rax
	popq	%rax
	movq	$1600, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$20
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$16, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$8, %rbx
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
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

