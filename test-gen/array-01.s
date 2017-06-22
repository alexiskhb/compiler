.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .fill 808,1,0
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
	pushq	$20
// generate_lvalue
// gen_start_address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$10
	movq	$0, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	leaq	(%rax,%rbx,8), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$5
	pushq	$5
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	movq	$0, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	(%rax,%rbx,8), %rax
	pushq	%rax
	pushq	$10
	popq	%rbx
	popq	%rax
	subq	%rbx, %rax
	pushq	%rax
// generate_lvalue
// gen_start_address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$9
	movq	$0, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	leaq	(%rax,%rbx,8), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$9
	movq	$0, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	(%rax,%rbx,8), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$10
	movq	$0, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	popq	%rax
	movq	(%rax,%rbx,8), %rax
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

