.__._fmt_int_:
	.string "%Ld"
.__._fmt_float_:
	.string "%lf"
.__._fmt_newline_:
	.string "
"
	.globl main
.data
	.__A: .fill 168,1,0
.data
	.__N: .quad 0
.data
	.__I: .quad 0
.data
	.__J: .quad 0
.data
	.__X: .double 0
.__.str0:
	.string " "
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$20, .__N
	call	.__FILL_ARRAY
	call	.__PRINT_ARRAY
	call	.__BUBBLE_SORT
	call	.__PRINT_ARRAY
	leaq	.__._fmt_newline_, %rdi
	call	printf
	call	.__FILL_ARRAY
	call	.__PRINT_ARRAY
	call	.__INSERTION_SORT
	call	.__PRINT_ARRAY
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	xorq	%rax, %rax
	ret
.__FILL_ARRAY:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	.__N, %rax
	negq	%rax
	pushq	%rax
	leaq	.__I, %rax
	xorq	%r13, %r13
	movq	%rax, %r14
	popq	(%r14)
	cmpq	(%r14), %r13
	jl	..L2
..L1:
	movq	.__I, %rax
	negq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__A, %rax
	movq	.__N, %r10
	pushq	%rax
	movq	.__I, %rax
	addq	%r10, %rax
	xorq	%r9, %r9
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
..L3:
	movq	.__I, %r13
	xorq	%r14, %r14
	cmpq	%r13, %r14
	jle	..L2
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L1
..L2:
	popq	%rbp
	ret
.__PRINT_ARRAY:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__I, %rax
	movq	.__N, %r13
	movq	%rax, %r14
	movq	$0, (%r14)
	cmpq	(%r14), %r13
	jl	..L5
..L4:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__I, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__._fmt_float_, %rdi
	movq	%r10, %rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__.str0, %rdi
	call	printf
..L6:
	movq	.__I, %r13
	movq	.__N, %r14
	cmpq	%r13, %r14
	jle	..L5
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L4
..L5:
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret
.__BUBBLE_SORT:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__I, %rax
	movq	.__N, %r13
	movq	%rax, %r14
	movq	$0, (%r14)
	cmpq	(%r14), %r13
	jl	..L8
..L7:
	leaq	.__J, %rax
	movq	%rax, %r14
	movq	$1, %r13
	pushq	.__I
	popq	(%r14)
	cmpq	(%r14), %r13
	jg	..L11
..L10:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	pushq	%r10
	pushq	%rax
	movq	.__J, %rax
	subq	$1, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setl	%al
	testq	%rax, %rax
	jz	..L13
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	movq	%r10, .__X
	leaq	.__A, %rax
	pushq	%rax
	movq	.__J, %rax
	subq	$1, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%r10
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	leaq	.__A, %rax
	pushq	.__X
	pushq	%rax
	movq	.__J, %rax
	subq	$1, %rax
	xorq	%r9, %r9
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	jmp	..L14
..L13:
..L14:
..L12:
	movq	.__J, %r13
	movq	$1, %r14
	cmpq	%r13, %r14
	jge	..L11
	leaq	.__J, %rax
	movq	%rax, %r12
	subq	$1, (%r12)
	jmp	..L10
..L11:
..L9:
	movq	.__I, %r13
	movq	.__N, %r14
	cmpq	%r13, %r14
	jle	..L8
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L7
..L8:
	popq	%rbp
	ret
.__INSERTION_SORT:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.__I, %rax
	movq	$1, %r10
	pushq	$1
	pushq	%rax
	movq	.__N, %rax
	subq	%r10, %rax
	movq	%rax, %r13
	popq	%r14
	popq	(%r14)
	cmpq	(%r14), %r13
	jl	..L16
..L15:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%rax
	movq	.__I, %rax
	subq	%r9, %rax
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	movq	%r10, .__X
	leaq	.__J, %rax
	pushq	.__I
	popq	(%rax)
..L18:
	xorq	%r11, %r11
	movq	.__J, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	testq	%rax, %rax
	jz	..L21
	leaq	.__A, %rax
	pushq	%rax
	movq	.__J, %rax
	subq	$1, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	movq	.__X, %r11
	movq	%r10, %rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	testq	%rax, %rax
	jz	..L21
	pushq	$1
	jmp	..L20
..L21:
	pushq	$0
..L20:
	popq	%rax
	testq	%rax, %rax
	jz	..L19
	leaq	.__A, %rax
	pushq	%rax
	movq	.__J, %rax
	subq	$1, %rax
	xorq	%r9, %r9
	movq	%rax, %r12
	imulq	$8, %r12
	popq	%r10
	movq	(%r10,%r12,1), %r10
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	%r10
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
	subq	$1, .__J
	jmp	..L18
..L19:
	leaq	.__A, %rax
	xorq	%r9, %r9
	pushq	.__X
	pushq	%rax
	movq	.__J, %rax
	subq	%r9, %rax
	movq	%rax, %rcx
	imulq	$8, %rcx
	popq	%rax
	popq	(%rax,%rcx,1)
..L17:
	movq	.__N, %rax
	subq	$1, %rax
	movq	.__I, %r13
	movq	%rax, %r14
	cmpq	%r13, %r14
	jle	..L16
	leaq	.__I, %rax
	movq	%rax, %r12
	addq	$1, (%r12)
	jmp	..L15
..L16:
	popq	%rbp
	ret

