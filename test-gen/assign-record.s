.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .fill 16,1,0
.data
	.__B: .fill 16,1,0
main:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	$10
	leaq	.__A, %rax
	pushq	%rax
	popq	%rax
	movq	$0, %rcx
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__A
	leaq	.__B, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	leaq	.__B, %rax
	pushq	%rax
	popq	%r11
	movq	$0, %r13
	movq	(%r11,%r13,1), %r11
	pushq	%r11
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

