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
	pushq	$5
	leaq	.__N, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__K, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$3
	leaq	.__D, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__DI, %rax
	pushq	%rax
	pushq	$0
	pushq	$0
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__DI, %rax
	pushq	%rax
	pushq	$0
	pushq	$1
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__DI, %rax
	pushq	%rax
	pushq	$0
	pushq	$2
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	popq	%rax
	negq	%rax
	pushq	%rax
	leaq	.__DI, %rax
	pushq	%rax
	pushq	$0
	pushq	$3
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__DJ, %rax
	pushq	%rax
	pushq	$0
	pushq	$0
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	popq	%rax
	negq	%rax
	pushq	%rax
	leaq	.__DJ, %rax
	pushq	%rax
	pushq	$0
	pushq	$1
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__DJ, %rax
	pushq	%rax
	pushq	$0
	pushq	$2
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$1
	leaq	.__DJ, %rax
	pushq	%rax
	pushq	$0
	pushq	$3
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	$0
	leaq	.__GOT0N, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L1:
	pushq	.__K
	pushq	.__N
	pushq	.__N
	popq	%r10
	popq	%rax
	imulq	%r10, %rax
	pushq	%rax
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setle	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L2
	pushq	.__I
	pushq	$0
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jnz	..L5
	pushq	.__J
	pushq	$0
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
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
	pushq	.__I
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
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
	pushq	.__J
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
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
	pushq	.__GOT0N
	popq	%rax
	testq	%rax, %rax
	jz	..L11
	pushq	.__D
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	leaq	.__D, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	jmp	..L12
..L11:
	pushq	.__D
	pushq	$1
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__D, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L12:
	jmp	..L4
..L3:
..L4:
	pushq	.__K
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__I
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$6, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	pushq	.__J
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%rcx
	imulq	$8, %rcx
	popq	%rax
	leaq	(%rax,%rcx,1), %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__I
	leaq	.__DI, %rax
	pushq	%rax
	pushq	$0
	pushq	.__D
	popq	%rax
	pushq	$4
	popq	%rbx
	xorq	%rdx, %rdx
	cqo
	idivq	%rbx
	movq	%rdx, %rax
	pushq	%rax
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	pushq	%r10
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__I, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__J
	leaq	.__DJ, %rax
	pushq	%rax
	pushq	$0
	pushq	.__D
	popq	%rax
	pushq	$4
	popq	%rbx
	xorq	%rdx, %rdx
	cqo
	idivq	%rbx
	movq	%rdx, %rax
	pushq	%rax
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	pushq	%r10
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
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
	pushq	.__I
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	pushq	$1
	pushq	.__N
	popq	%rax
	pushq	$2
	popq	%rbx
	xorq	%rdx, %rdx
	cqo
	idivq	%rbx
	movq	%rdx, %rax
	pushq	%rax
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	popq	%r10
	popq	%rax
	imulq	%r10, %rax
	pushq	%rax
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L22
	pushq	.__J
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	pushq	.__N
	popq	%rax
	pushq	$2
	popq	%rbx
	xorq	%rdx, %rdx
	cqo
	idivq	%rbx
	movq	%rdx, %rax
	pushq	%rax
	popq	%r10
	popq	%rax
	imulq	%r10, %rax
	pushq	%rax
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	sete	%al
	pushq	%rax
	popq	%rax
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
	pushq	$1
	leaq	.__GOT0N, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	jmp	..L18
..L17:
..L18:
	jmp	..L1
..L2:
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L26
..L25:
	pushq	$0
	leaq	.__J, %rax
	pushq	%rax
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L29
..L28:
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__I
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$6, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	pushq	.__J
	movq	$0, %r9
	popq	%rax
	subq	%r9, %rax
	movq	$1, %r9
	imulq	%r9, %rax
	popq	%r9
	addq	%r9, %rax
	pushq	%rax
	popq	%r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	pushq	%r10
	leaq	.__._fmt_int_, %rdi
	popq	%rsi
	call	printf
	leaq	.__.str0, %rdi
	call	printf
..L30:
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	pushq	.__J
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L29
	leaq	.__J, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L28
..L29:
	leaq	.__._fmt_newline_, %rdi
	call	printf
..L27:
	pushq	.__N
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	pushq	.__I
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L26
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L25
..L26:
	popq	%rbp
	xorq	%rax, %rax
	ret

