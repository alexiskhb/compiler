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
	leaq	.__I, %rax
	movq	%rax, %r14
	movq	$1, (%r14)
	movq	$100, %r13
	cmpq	(%r14), %r13
	jl	..L2
..L1:
	addq	$4, .__K
..L3:
	movq	.__I, %r13
	movq	$100, %r14
	cmpq	%r13, %r14
	jle	..L2
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L1
..L2:
	leaq	.__._fmt_int_, %rdi
	movq	.__K, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$0, .__K
	leaq	.__I, %rax
	movq	%rax, %r14
	movq	$1, (%r14)
	movq	$1000, %r13
	cmpq	(%r14), %r13
	jl	..L5
..L4:
	addq	$4, .__K
	movq	.__I, %rdx
	xorq	%rax, %rax
	cmpq	$100, %rdx
	sete	%al
	testq	%rax, %rax
	jz	..L7
	jmp	..L5
	jmp	..L8
..L7:
..L8:
..L6:
	movq	.__I, %r13
	movq	$1000, %r14
	cmpq	%r13, %r14
	jle	..L5
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L4
..L5:
	leaq	.__._fmt_int_, %rdi
	movq	.__K, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	movq	$0, .__K
	leaq	.__I, %rax
	movq	%rax, %r14
	movq	$200, (%r14)
	movq	$1, %r13
	cmpq	(%r14), %r13
	jg	..L10
..L9:
	movq	.__I, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$2, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	testq	%rax, %rax
	jz	..L12
	jmp	..L11
	jmp	..L13
..L12:
..L13:
	addq	$4, .__K
	leaq	.__J, %rax
	movq	%rax, %r14
	movq	$1, (%r14)
	movq	$1000, %r13
	cmpq	(%r14), %r13
	jl	..L17
..L16:
	jmp	..L17
	addq	$1, .__K
..L18:
	movq	.__J, %r13
	movq	$1000, %r14
	cmpq	%r13, %r14
	jle	..L17
	leaq	.__J, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L16
..L17:
..L11:
	movq	.__I, %r13
	movq	$1, %r14
	cmpq	%r13, %r14
	jge	..L10
	leaq	.__I, %rax
	movq	%rax, %r12
	subq	$1, (%r12)
	jmp	..L9
..L10:
	leaq	.__._fmt_int_, %rdi
	movq	.__K, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
	leaq	.__I, %rax
	movq	%rax, %r14
	movq	$1, (%r14)
	movq	$1, %r13
	cmpq	(%r14), %r13
	jl	..L20
..L19:
	leaq	.__._fmt_int_, %rdi
	movq	.__K, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L21:
	movq	.__I, %r13
	movq	$1, %r14
	cmpq	%r13, %r14
	jle	..L20
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L19
..L20:
	leaq	.__I, %rax
	xorq	%r13, %r13
	movq	%rax, %r14
	movq	$1, (%r14)
	cmpq	(%r14), %r13
	jl	..L23
..L22:
	leaq	.__._fmt_int_, %rdi
	xorq	%rsi, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L24:
	movq	.__I, %r13
	xorq	%r14, %r14
	cmpq	%r13, %r14
	jle	..L23
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L22
..L23:
	leaq	.__I, %rax
	movq	%rax, %r14
	movq	$0, (%r14)
	movq	$1, %r13
	cmpq	(%r14), %r13
	jg	..L26
..L25:
	leaq	.__._fmt_int_, %rdi
	xorq	%rsi, %rsi
	call	printf
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L27:
	movq	.__I, %r13
	movq	$1, %r14
	cmpq	%r13, %r14
	jge	..L26
	leaq	.__I, %rax
	movq	%rax, %r12
	subq	$1, (%r12)
	jmp	..L25
..L26:
	popq	%rbp
	xorq	%rax, %rax
	ret

