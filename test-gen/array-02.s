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
// start block
	pushq	$415
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
	pushq	$416
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$6
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$2
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$6
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rax
	popq	(%rax)
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$2
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	$3
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$6
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$0
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$0
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$0
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$4
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$1
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$5
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
// generate_lvalue
// gen_start_address
// generate array start address
	leaq	.__A, %rax
	pushq	%rax
// gen_index
	pushq	$0
	pushq	$0
	movq	$2, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$6, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$0
	movq	$1, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$4, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	pushq	$0
	movq	$3, %rbx
	popq	%rax
	subq	%rbx, %rax
	movq	$1, %rbx
	imulq	%rbx, %rax
	popq	%rbx
	addq	%rbx, %rax
	pushq	%rax
	popq	%rbx
	imulq	$8, %rbx
	popq	%rax
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
// end generate_lvalue
	popq	%rbx
	popq	%rax
	subq	%rbx, %rax
	pushq	%rax
	pushq	$8
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	popq	%rax
	pushq	(%rax)
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

