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
// start block
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
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__C, %rax
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
	imulq	$24, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$16, %rbx
	leaq	(%rax,%rbx,1), %rax
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
	popq	%rbx
	popq	%rax
	movq	%rax, %xmm0
	movq	%rbx, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
// generate record start address
// generate_lvalue
// gen_start_address
// generate array start address
	pushq	.__PC
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
	imulq	$24, %rbx
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
	pushq	.__PC
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
	imulq	$24, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	movq	$16, %rbx
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
	leaq	.__C, %rax
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
	imulq	$24, %rbx
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

