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
	leaq	.__A, %rax
	xorq	%rcx, %rcx
	movq	$10, (%rax,%rcx,1)
	leaq	.__B, %rax
	pushq	.__A
	popq	(%rax)
	leaq	.__B, %rax
	movq	%rax, %r11
	xorq	%r13, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_int_, %rdi
	movq	%r11, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

