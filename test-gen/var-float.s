.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .double 0
.data
	.__BB: .double 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

