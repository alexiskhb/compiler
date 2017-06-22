.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__P: .fill 16,1,0
.__.str0:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
	pushq	$10
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$0, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$20
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$8, %rbx
	leaq	(%rax,%rbx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$0, %rbx
	movq	(%rax,%rbx,1), %rax
	pushq	%rax
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
// generate record start address
	leaq	.__P, %rax
	pushq	%rax
	popq	%rax
	movq	$8, %rbx
	movq	(%rax,%rbx,1), %rax
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

