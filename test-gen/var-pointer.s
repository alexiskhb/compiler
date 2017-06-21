.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
main:
	pushq	%rbp
	movq	%rsp, %rbp
// pointer A
// pointer BB
// start block
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

