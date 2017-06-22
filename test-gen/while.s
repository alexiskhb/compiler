.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__I: .quad 0
.data
	.__K: .quad 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
..L1:
	pushq	.__I
	pushq	$100
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L2
// start block
	pushq	.__I
	pushq	$1
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__K
	pushq	$3
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// end block
	jmp	..L1
..L2:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L3:
	pushq	.__I
	pushq	$1000
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L4
// start block
	pushq	.__I
	pushq	$1
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__K
	pushq	$3
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__I
	pushq	$100
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	sete	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L5
	jmp	..L4
	jmp	..L6
..L5:
..L6:
// end block
	jmp	..L3
..L4:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L7:
	pushq	.__I
	pushq	$200
	popq	%rbx
	popq	%rax
	cmpq	%rbx, %rax
	movq	$0, %rax
	setne	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L8
// start block
	pushq	.__I
	pushq	$1
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__I
	popq	%rax
	pushq	$2
	popq	%rbx
	xorq	%rdx, %rdx
	cqo
	idivq	%rbx
	movq	%rdx, %rax
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L9
	jmp	..L7
	jmp	..L10
..L9:
..L10:
	pushq	.__K
	pushq	$3
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L13:
	pushq	$1
	popq	%rax
	testq	%rax, %rax
	jz	..L14
	jmp	..L14
	jmp	..L13
..L14:
// end block
	jmp	..L7
..L8:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L15:
	pushq	$0
	popq	%rax
	testq	%rax, %rax
	jz	..L16
	pushq	$0
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	jmp	..L15
..L16:
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

