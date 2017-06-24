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
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	pushq	$100
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L2
..L1:
	pushq	.__K
	pushq	$4
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L3:
	pushq	$100
	pushq	.__I
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L2
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
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
	pushq	$1000
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L5
..L4:
	pushq	.__K
	pushq	$4
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__I
	pushq	$100
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L7
	jmp	..L5
	jmp	..L8
..L7:
..L8:
..L6:
	pushq	$1000
	pushq	.__I
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L5
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
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
	pushq	$1
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jg	..L10
..L9:
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
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__J, %rax
	pushq	%rax
	pushq	$1000
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L17
..L16:
	jmp	..L17
	pushq	.__K
	pushq	$1
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L18:
	pushq	$1000
	pushq	.__J
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L17
	leaq	.__J, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L16
..L17:
..L11:
	pushq	$1
	pushq	.__I
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jge	..L10
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	subq	$1, (%r12)
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
	pushq	$1
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
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
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L20
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L19
..L20:
	pushq	$1
	leaq	.__I, %rax
	pushq	%rax
	pushq	$0
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
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
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L23
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L22
..L23:
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	pushq	$1
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
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
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jge	..L26
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	subq	$1, (%r12)
	jmp	..L25
..L26:
	popq	%rbp
	xorq	%rax, %rax
	ret

