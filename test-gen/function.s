.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.__.str2:
	.string "ok"
.__.str3:
	.string "error"
.__.str4:
	.string "ok"
.__.str5:
	.string "error"
.__.str0:
	.string "call foo1"
.__.str1:
	.string "call foo0"
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
	subq	$8, %rsp
	call	.__FOO222
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	subq	$8, %rsp
	call	.__FOO1
	popq	%rax
	testq	%rax, %rax
	jz	..L1
	leaq	.__.str2, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L2
..L1:
	leaq	.__.str3, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L2:
	subq	$8, %rsp
	call	.__FOO0
	popq	%rax
	xorq	$1, %rax
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L3
	leaq	.__.str4, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L4
..L3:
	leaq	.__.str5, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L4:
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret
.__FOO1:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
// start block
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret
// end block
	popq	%rbp
	ret
.__FOO0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
// start block
	leaq	.__.str1, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret
// end block
	popq	%rbp
	ret
.__FOO222:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
// start block
	popq	%rbp
	ret
// end block
	popq	%rbp
	ret

