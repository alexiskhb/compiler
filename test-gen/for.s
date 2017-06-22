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
	.__J: .quad 0
.data
	.__K: .quad 0
main:
	pushq	%rbp
	movq	%rsp, %rbp
// start block
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$100
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jl	..L2
..L1:
// start block
	pushq	.__K
	pushq	$4
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// end block
..L3:
	pushq	$100
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jle	..L2
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	addq	$1, (%rax)
	jmp	..L1
..L2:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$0
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1000
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jl	..L5
..L4:
// start block
	pushq	.__K
	pushq	$4
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
	jz	..L7
	jmp	..L5
	jmp	..L8
..L7:
..L8:
// end block
..L6:
	pushq	$1000
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jle	..L5
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	addq	$1, (%rax)
	jmp	..L4
..L5:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$0
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$200
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jg	..L10
..L9:
// start block
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
	jz	..L12
	jmp	..L11
	jmp	..L13
..L12:
..L13:
	pushq	.__K
	pushq	$4
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1000
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jl	..L17
..L16:
// start block
	jmp	..L17
	pushq	.__K
	pushq	$1
	popq	%rbx
	popq	%rax
	addq	%rbx, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
// end block
..L18:
	pushq	$1000
	pushq	.__J
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jle	..L17
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	addq	$1, (%rax)
	jmp	..L16
..L17:
// end block
..L11:
	pushq	$1
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jge	..L10
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	subq	$1, (%rax)
	jmp	..L9
..L10:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jl	..L20
..L19:
	pushq	.__K
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L21:
	pushq	$1
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jle	..L20
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	addq	$1, (%rax)
	jmp	..L19
..L20:
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jl	..L23
..L22:
	pushq	$0
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L24:
	pushq	$0
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jle	..L23
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	addq	$1, (%rax)
	jmp	..L22
..L23:
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	movq	(%rax), %rbx
	popq	%rax
	cmpq	%rbx, %rax
	jg	..L26
..L25:
	pushq	$0
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L27:
	pushq	$1
	pushq	.__I
	popq	%rax
	popq	%rbx
	cmpq	%rax, %rbx
	jge	..L26
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	subq	$1, (%rax)
	jmp	..L25
..L26:
// end block
	popq	%rbp
	xorq	%rax, %rax
	ret

