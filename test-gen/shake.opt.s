.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__K: .quad 0
.data
	.__I: .quad 0
.data
	.__J: .quad 0
.data
	.__D: .quad 0
.data
	.__N: .quad 0
.data
	.__A: .fill 288,1,0
.data
	.__DI: .fill 32,1,0
.data
	.__DJ: .fill 32,1,0
.data
	.__GOT0N: .quad 0
.__.str0:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$5, .__N
	movq	$0, .__K
	movq	$0, .__I
	movq	$0, .__J
	movq	$3, .__D
	leaq	.__DI, %rax
	xorq	%r9, %r9
	pushq	$0
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DI, %rax
	xorq	%r9, %r9
	pushq	$1
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DI, %rax
	xorq	%r9, %r9
	pushq	$1
	pushq	%rax
	movq	$2, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	movq	$1, %rax
	negq	%rax
	pushq	%rax
	leaq	.__DI, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	$3, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DJ, %rax
	xorq	%r9, %r9
	pushq	$1
	pushq	%rax
	xorq	%rax, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	movq	$1, %rax
	negq	%rax
	pushq	%rax
	leaq	.__DJ, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	$1, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DJ, %rax
	xorq	%r9, %r9
	pushq	$0
	pushq	%rax
	movq	$2, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DJ, %rax
	xorq	%r9, %r9
	pushq	$1
	pushq	%rax
	movq	$3, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	movq	$0, .__GOT0N
..L1:
	movq	.__N, %r10
	movq	.__N, %rax
	imulq	%r10, %rax
	movq	%rax, %r11
	movq	.__K, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	testq	%rax, %rax
	jz	..L2
	xorq	%r11, %r11
	movq	.__I, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jnz	..L5
	xorq	%r11, %r11
	movq	.__J, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jnz	..L5
	pushq	$0
	jmp	..L6
..L5:
	pushq	$1
..L6:
	popq	%rax
	testq	%rax, %rax
	jnz	..L7
	movq	.__N, %rax
	subq	$1, %rax
	movq	%rax, %r11
	movq	.__I, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jnz	..L7
	pushq	$0
	jmp	..L8
..L7:
	pushq	$1
..L8:
	popq	%rax
	testq	%rax, %rax
	jnz	..L9
	movq	.__N, %rax
	subq	$1, %rax
	movq	%rax, %r11
	movq	.__J, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jnz	..L9
	pushq	$0
	jmp	..L10
..L9:
	pushq	$1
..L10:
	popq	%rax
	testq	%rax, %rax
	jz	..L3
	movq	.__GOT0N, %rax
	testq	%rax, %rax
	jz	..L11
	subq	$1, .__D
	jmp	..L12
..L11:
	addq	$1, .__D
..L12:
	jmp	..L4
..L3:
..L4:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	.__K
	pushq	%rax
	movq	.__I, %rax
	subq	%r9, %rax
	imulq	$6, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__DI, %rax
	pushq	.__I
	pushq	%rax
	movq	.__D, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$4, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	popq	%rax
	addq	%r10, %rax
	movq	%rax, .__I
	leaq	.__DJ, %rax
	pushq	.__J
	pushq	%rax
	movq	.__D, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$4, %rbx
	idivq	%rbx
	movq	%rdx, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	popq	%rax
	addq	%r10, %rax
	movq	%rax, .__J
	addq	$1, .__K
	movq	.__N, %rax
	subq	$1, %rax
	pushq	.__I
	pushq	%rax
	movq	.__N, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$2, %rbx
	idivq	%rbx
	movq	%rdx, %r10
	movq	$1, %rax
	subq	%r10, %rax
	movq	%rax, %r10
	popq	%rax
	imulq	%r10, %rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jz	..L22
	movq	.__N, %rax
	subq	$1, %rax
	pushq	.__J
	pushq	%rax
	movq	.__N, %rax
	xorq	%rdx, %rdx
	cqo
	movq	$2, %rbx
	idivq	%rbx
	movq	%rdx, %r10
	popq	%rax
	imulq	%r10, %rax
	movq	%rax, %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	testq	%rax, %rax
	jz	..L22
	pushq	$1
	jmp	..L21
..L22:
	pushq	$0
..L21:
	popq	%rax
	testq	%rax, %rax
	jz	..L17
	movq	$1, .__GOT0N
	jmp	..L18
..L17:
..L18:
	jmp	..L1
..L2:
	leaq	.__I, %rax
	movq	$1, %r10
	pushq	$0
	pushq	%rax
	movq	.__N, %rax
	subq	%r10, %rax
	movq	%rax, %r13
	popq	%r14
	popq	(%r14)
	cmpq	(%r14), %r13
	jl	..L26
..L25:
	leaq	.__J, %rax
	movq	$1, %r10
	pushq	$0
	pushq	%rax
	movq	.__N, %rax
	subq	%r10, %rax
	movq	%rax, %r13
	popq	%r14
	popq	(%r14)
	cmpq	(%r14), %r13
	jl	..L29
..L28:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__I, %rax
	subq	%r9, %rax
	imulq	$6, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_int_, %rdi
	movq	%r10, %rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
..L30:
	movq	.__N, %rax
	subq	$1, %rax
	movq	.__J, %r13
	movq	%rax, %r14
	cmpq	%r13, %r14
	jle	..L29
	leaq	.__J, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L28
..L29:
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L27:
	movq	.__N, %rax
	subq	$1, %rax
	movq	.__I, %r13
	movq	%rax, %r14
	cmpq	%r13, %r14
	jle	..L26
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L25
..L26:
	popq	%rbp
	xorq	%rax, %rax
	ret

