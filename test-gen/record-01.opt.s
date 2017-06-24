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
	leaq	.__P, %rax
	xorq	%rcx, %rcx
	movq	$10, (%rax,%rcx,1)
	leaq	.__P, %rax
	movq	$8, %rcx
	movq	$20, (%rax,%rcx,1)
	leaq	.__P, %rax
	movq	%rax, %r11
	xorq	%r13, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_int_, %rdi
	movq	%r11, %rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__P, %rax
	movq	%rax, %r11
	movq	$8, %r13
	movq	(%r11,%r13,1), %r11
	leaq	.__._fmt_int_, %rdi
	movq	%r11, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

