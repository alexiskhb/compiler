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
	xorq	%rax, %rax
	testq	%rax, %rax
	jnz	..L1
	xorq	%rax, %rax
	testq	%rax, %rax
	jnz	..L1
	pushq	$0
	jmp	..L2
..L1:
	pushq	$1
..L2:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	xorq	%rax, %rax
	testq	%rax, %rax
	jnz	..L3
	movq	$1, %rax
	testq	%rax, %rax
	jnz	..L3
	pushq	$0
	jmp	..L4
..L3:
	pushq	$1
..L4:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$1, %rax
	testq	%rax, %rax
	jnz	..L5
	xorq	%rax, %rax
	testq	%rax, %rax
	jnz	..L5
	pushq	$0
	jmp	..L6
..L5:
	pushq	$1
..L6:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$1, %rax
	testq	%rax, %rax
	jnz	..L7
	movq	$1, %rax
	testq	%rax, %rax
	jnz	..L7
	pushq	$0
	jmp	..L8
..L7:
	pushq	$1
..L8:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L10
	jmp	..L10
	pushq	$1
	jmp	..L9
..L10:
	pushq	$0
..L9:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L12
	movq	$1, %rax
	testq	%rax, %rax
	jz	..L12
	pushq	$1
	jmp	..L11
..L12:
	pushq	$0
..L11:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$1, %rax
	testq	%rax, %rax
	jz	..L14
	jmp	..L14
	pushq	$1
	jmp	..L13
..L14:
	pushq	$0
..L13:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$1, %rax
	testq	%rax, %rax
	jz	..L16
	movq	$1, %rax
	testq	%rax, %rax
	jz	..L16
	pushq	$1
	jmp	..L15
..L16:
	pushq	$0
..L15:
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret

