.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.__.str0:
	.string "call foo"
.__.str1:
	.string "error"
main:
	pushq	%rbp
	movq	%rsp, %rbp
	call	.__FOO
	popq	%rbp
	xorq	%rax, %rax
	ret
.__FOO:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret
	leaq	.__.str1, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret

