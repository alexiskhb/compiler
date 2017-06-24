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
	pushq	$20
	leaq	.__N, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
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
	subq	$0, %rsp
	pushq	.__N
	popq	%rax
	negq	%rax
	pushq	%rax
	leaq	.__I, %rax
	pushq	%rax
	pushq	$0
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L2
..L1:
	pushq	.__I
	popq	%rax
	negq	%rax
	pushq	%rax
	popq	%rax
	cvtsi2sd	%rax, %xmm0
	movq	%xmm0, %rax
	pushq	%rax
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__I
	pushq	.__N
	popq	%r10
	popq	%rax
	addq	%r10, %rax
	pushq	%rax
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
..L3:
	pushq	$0
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
	popq	%rbp
	ret
.__PRINT_ARRAY:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	pushq	.__N
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L5
..L4:
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__I
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
	leaq	.__._fmt_float_, %rdi
	popq	%rax
	movq	%rax, %xmm0
	movq	$1, %rax
	call	printf
	leaq	.__.str0, %rdi
	call	printf
..L6:
	pushq	.__N
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
	leaq	.__._fmt_newline_, %rdi
	call	printf
	popq	%rbp
	ret
.__BUBBLE_SORT:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
	pushq	$0
	leaq	.__I, %rax
	pushq	%rax
	pushq	.__N
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jl	..L8
..L7:
	pushq	.__I
	leaq	.__J, %rax
	pushq	%rax
	pushq	$1
	popq	%r13
	popq	%r14
	popq	(%r14)
	movq	(%r14), %r14
	cmpq	%r14, %r13
	jg	..L11
..L10:
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
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
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
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
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setl	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L13
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
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
	leaq	.__X, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
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
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
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
	pushq	.__X
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
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
	jmp	..L14
..L13:
..L14:
..L12:
	pushq	$1
	pushq	.__J
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jge	..L11
	leaq	.__J, %rax
	pushq	%rax
	popq	%r12
	subq	$1, (%r12)
	jmp	..L10
..L11:
..L9:
	pushq	.__N
	pushq	.__I
	popq	%r13
	popq	%r14
	cmpq	%r13, %r14
	jle	..L8
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L7
..L8:
	popq	%rbp
	ret
.__INSERTION_SORT:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$0, %rsp
	pushq	$1
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
	jl	..L16
..L15:
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__I
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
	leaq	.__X, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	pushq	.__I
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
..L18:
	pushq	.__J
	pushq	$0
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	pushq	%rax
	popq	%rax
	testq	%rax, %rax
	jz	..L21
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
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
	pushq	.__X
	popq	%r11
	popq	%rdx
	xorq	%rax, %rax
	cmpq	%r11, %rdx
	setg	%al
	pushq	%rax
	popq	%rax
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
	pushq	$0
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
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
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
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
	pushq	.__J
	pushq	$1
	popq	%r10
	popq	%rax
	subq	%r10, %rax
	pushq	%rax
	leaq	.__J, %rax
	pushq	%rax
	popq	%rax
	popq	(%rax)
	jmp	..L18
..L19:
	pushq	.__X
	leaq	.__A, %rax
	pushq	%rax
	pushq	$0
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
..L17:
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
	jle	..L16
	leaq	.__I, %rax
	pushq	%rax
	popq	%r12
	addq	$1, (%r12)
	jmp	..L15
..L16:
	popq	%rbp
	ret

