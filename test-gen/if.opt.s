.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .quad 0
.data
	.__B: .quad 0
.__.str0:
	.string "not ok"
.__.str1:
	.string "ok"
.__.str2:
	.string "ok"
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$10, .__A
	movq	$10, .__B
	movq	.__B, %r11
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setne	%al
	testq	%rax, %rax
	jz	..L1
	leaq	.__.str0, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L2
..L1:
	leaq	.__.str1, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L2:
	movq	.__B, %r11
	movq	.__A, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jz	..L3
	leaq	.__.str2, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L4
..L3:
..L4:
	popq	%rbp
	xorq	%rax, %rax
	ret

