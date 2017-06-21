.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.__.str0:
	.string "ababaca
"
.__.str1:
	.string "acaba
"
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__.str1, %rdi
	call	printf
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

