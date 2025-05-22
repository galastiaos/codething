	.file	"main.c"
	.text
	.globl	board
	.bss
	.align 32
	.type	board, @object
	.size	board, 64
board:
	.zero	64
	.globl	input
	.type	input, @object
	.size	input, 5
input:
	.zero	5
	.globl	input_pos
	.align 4
	.type	input_pos, @object
	.size	input_pos, 4
input_pos:
	.zero	4
	.globl	current_player
	.data
	.type	current_player, @object
	.size	current_player, 1
current_player:
	.byte	88
	.text
	.globl	init_board
	.type	init_board, @function
init_board:
.LFB4877:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -8(%rbp)
	jmp	.L2
.L11:
	movl	$0, -4(%rbp)
	jmp	.L3
.L10:
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$31, %eax
	addl	%eax, %edx
	andl	$1, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	cmpl	$1, %eax
	jne	.L4
	cmpl	$2, -8(%rbp)
	jle	.L5
	cmpl	$4, -8(%rbp)
	jle	.L6
	movl	$88, %eax
	jmp	.L9
.L6:
	movl	$32, %eax
	jmp	.L9
.L5:
	movl	$79, %eax
	jmp	.L9
.L4:
	movl	$46, %eax
.L9:
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	-8(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$3, %rcx
	addq	%rdx, %rcx
	leaq	board(%rip), %rdx
	addq	%rcx, %rdx
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
.L3:
	cmpl	$7, -4(%rbp)
	jle	.L10
	addl	$1, -8(%rbp)
.L2:
	cmpl	$7, -8(%rbp)
	jle	.L11
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4877:
	.size	init_board, .-init_board
	.globl	draw_text
	.type	draw_text, @function
draw_text:
.LFB4878:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movl	%ecx, -76(%rbp)
	movl	%r8d, -80(%rbp)
	movl	%r9d, -84(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	-84(%rbp), %edx
	movq	-72(%rbp), %rcx
	movq	-64(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	TTF_RenderText_Blended@PLT
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_CreateTextureFromSurface@PLT
	movq	%rax, -40(%rbp)
	movl	-76(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, -28(%rbp)
	movq	-48(%rbp), %rax
	movl	16(%rax), %eax
	movl	%eax, -24(%rbp)
	movq	-48(%rbp), %rax
	movl	20(%rax), %eax
	movl	%eax, -20(%rbp)
	leaq	-32(%rbp), %rdx
	movq	-40(%rbp), %rsi
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_RenderCopy@PLT
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_FreeSurface@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyTexture@PLT
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4878:
	.size	draw_text, .-draw_text
	.section	.rodata
.LC0:
	.string	"Player %c - Move: %s"
	.text
	.globl	draw_board
	.type	draw_board, @function
draw_board:
.LFB4879:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$168, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-152(%rbp), %rax
	movl	$255, %r8d
	movl	$200, %ecx
	movl	$200, %edx
	movl	$200, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_RenderClear@PLT
	movl	$0, -144(%rbp)
	jmp	.L15
.L26:
	movl	$0, -140(%rbp)
	jmp	.L16
.L25:
	movl	-140(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, -128(%rbp)
	movl	-144(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, -124(%rbp)
	movl	$80, -120(%rbp)
	movl	$80, -116(%rbp)
	movl	-140(%rbp), %edx
	movl	-144(%rbp), %eax
	addl	%edx, %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L17
	movq	-152(%rbp), %rax
	movl	$255, %r8d
	movl	$240, %ecx
	movl	$240, %edx
	movl	$240, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	jmp	.L18
.L17:
	movq	-152(%rbp), %rax
	movl	$255, %r8d
	movl	$100, %ecx
	movl	$100, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
.L18:
	leaq	-128(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_RenderFillRect@PLT
	movl	-140(%rbp), %eax
	cltq
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$88, %al
	je	.L19
	movl	-140(%rbp), %eax
	cltq
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$79, %al
	jne	.L20
.L19:
	movl	-140(%rbp), %eax
	cltq
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$79, %al
	jne	.L21
	movl	$255, %ecx
	jmp	.L22
.L21:
	movl	$0, %ecx
.L22:
	movl	-140(%rbp), %eax
	cltq
	movl	-144(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$88, %al
	jne	.L23
	movl	$255, %esi
	jmp	.L24
.L23:
	movl	$0, %esi
.L24:
	movq	-152(%rbp), %rax
	movl	$255, %r8d
	movl	$0, %edx
	movq	%rax, %rdi
	call	SDL_SetRenderDrawColor@PLT
	movl	-140(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	addl	$20, %eax
	movl	%eax, -112(%rbp)
	movl	-144(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	addl	$20, %eax
	movl	%eax, -108(%rbp)
	movl	$40, -104(%rbp)
	movl	$40, -100(%rbp)
	leaq	-112(%rbp), %rdx
	movq	-152(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	SDL_RenderFillRect@PLT
.L20:
	addl	$1, -140(%rbp)
.L16:
	cmpl	$7, -140(%rbp)
	jle	.L25
	addl	$1, -144(%rbp)
.L15:
	cmpl	$7, -144(%rbp)
	jle	.L26
	movl	$0, -136(%rbp)
	jmp	.L27
.L28:
	movl	-136(%rbp), %eax
	addl	$65, %eax
	movb	%al, -96(%rbp)
	movb	$0, -95(%rbp)
	movl	-164(%rbp), %ecx
	movb	$0, %cl
	movl	$0, %eax
	movb	%al, %ch
	andl	$-16711681, %ecx
	movl	%ecx, %eax
	orl	$-16777216, %eax
	movl	%eax, -164(%rbp)
	movl	-136(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	leal	30(%rax), %ecx
	leaq	-96(%rbp), %rdx
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rax
	movl	-164(%rbp), %r9d
	movl	$650, %r8d
	movq	%rax, %rdi
	call	draw_text
	addl	$1, -136(%rbp)
.L27:
	cmpl	$7, -136(%rbp)
	jle	.L28
	movl	$0, -132(%rbp)
	jmp	.L29
.L30:
	movl	-132(%rbp), %eax
	movl	%eax, %edx
	movl	$56, %eax
	subl	%edx, %eax
	movb	%al, -96(%rbp)
	movb	$0, -95(%rbp)
	movl	-168(%rbp), %ecx
	movb	$0, %cl
	movl	$0, %eax
	movb	%al, %ch
	andl	$-16711681, %ecx
	movl	%ecx, %eax
	orl	$-16777216, %eax
	movl	%eax, -168(%rbp)
	movl	-132(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	leal	30(%rax), %ecx
	leaq	-96(%rbp), %rdx
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rax
	movl	-168(%rbp), %r9d
	movl	%ecx, %r8d
	movl	$650, %ecx
	movq	%rax, %rdi
	call	draw_text
	addl	$1, -132(%rbp)
.L29:
	cmpl	$7, -132(%rbp)
	jle	.L30
	movzbl	current_player(%rip), %eax
	movsbl	%al, %edx
	leaq	-96(%rbp), %rax
	leaq	input(%rip), %r8
	movl	%edx, %ecx
	leaq	.LC0(%rip), %rdx
	movl	$64, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	movb	$20, %bl
	movl	$20, %eax
	movb	%al, %bh
	movl	%ebx, %eax
	andl	$-16711681, %eax
	orl	$13107200, %eax
	movl	%eax, %ebx
	movl	%ebx, %eax
	orl	$-16777216, %eax
	movl	%eax, %ebx
	leaq	-96(%rbp), %rdx
	movq	-160(%rbp), %rsi
	movq	-152(%rbp), %rax
	movl	%ebx, %r9d
	movl	$680, %r8d
	movl	$10, %ecx
	movq	%rax, %rdi
	call	draw_text
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_RenderPresent@PLT
	nop
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L31
	call	__stack_chk_fail@PLT
.L31:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4879:
	.size	draw_board, .-draw_board
	.globl	is_valid_move
	.type	is_valid_move, @function
is_valid_move:
.LFB4880:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	%r8d, %eax
	movb	%al, -36(%rbp)
	cmpl	$0, -28(%rbp)
	js	.L33
	cmpl	$7, -28(%rbp)
	jg	.L33
	cmpl	$0, -32(%rbp)
	js	.L33
	cmpl	$7, -32(%rbp)
	jg	.L33
	movl	-28(%rbp), %eax
	cltq
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L34
.L33:
	movl	$0, %eax
	jmp	.L35
.L34:
	movl	-28(%rbp), %eax
	subl	-20(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-32(%rbp), %eax
	subl	-24(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	cmpl	$1, %eax
	jne	.L36
	cmpb	$88, -36(%rbp)
	jne	.L37
	cmpl	$-1, -12(%rbp)
	je	.L38
.L37:
	cmpb	$79, -36(%rbp)
	jne	.L36
	cmpl	$1, -12(%rbp)
	jne	.L36
.L38:
	movl	$1, %eax
	jmp	.L35
.L36:
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	cmpl	$2, %eax
	jne	.L39
	cmpb	$88, -36(%rbp)
	jne	.L40
	cmpl	$-2, -12(%rbp)
	je	.L41
.L40:
	cmpb	$79, -36(%rbp)
	jne	.L39
	cmpl	$2, -12(%rbp)
	jne	.L39
.L41:
	movl	-20(%rbp), %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -8(%rbp)
	movl	-24(%rbp), %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L42
	movl	-8(%rbp), %eax
	cltq
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -36(%rbp)
	je	.L42
	movl	$2, %eax
	jmp	.L35
.L42:
	movl	$0, %eax
	jmp	.L35
.L39:
	movl	$0, %eax
.L35:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4880:
	.size	is_valid_move, .-is_valid_move
	.globl	make_move
	.type	make_move, @function
make_move:
.LFB4881:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	%r8d, %eax
	movb	%al, -36(%rbp)
	movsbl	-36(%rbp), %edi
	movl	-32(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-24(%rbp), %esi
	movl	-20(%rbp), %eax
	movl	%edi, %r8d
	movl	%eax, %edi
	call	is_valid_move
	movl	%eax, -12(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L50
	movl	-28(%rbp), %eax
	cltq
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rax, %rdx
	movzbl	-36(%rbp), %eax
	movb	%al, (%rdx)
	movl	-20(%rbp), %eax
	cltq
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movb	$32, (%rax)
	cmpl	$2, -12(%rbp)
	jne	.L47
	movl	-20(%rbp), %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -8(%rbp)
	movl	-24(%rbp), %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movb	$32, (%rax)
.L47:
	movzbl	current_player(%rip), %eax
	cmpb	$88, %al
	jne	.L48
	movl	$79, %eax
	jmp	.L49
.L48:
	movl	$88, %eax
.L49:
	movb	%al, current_player(%rip)
	jmp	.L44
.L50:
	nop
.L44:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4881:
	.size	make_move, .-make_move
	.globl	parse_move
	.type	parse_move, @function
parse_move:
.LFB4882:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	cmpq	$4, %rax
	je	.L52
	movl	$0, %eax
	jmp	.L53
.L52:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L54
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	addq	$1, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$2048, %eax
	testl	%eax, %eax
	je	.L54
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	addq	$2, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L54
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	addq	$3, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$2048, %eax
	testl	%eax, %eax
	jne	.L55
.L54:
	movl	$0, %eax
	jmp	.L53
.L55:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	toupper@PLT
	leal	-65(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	$56, %edx
	subl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	toupper@PLT
	leal	-65(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	addq	$3, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	$56, %edx
	subl	%eax, %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	js	.L56
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	jg	.L56
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	js	.L56
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	jg	.L56
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	js	.L56
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	jg	.L56
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	js	.L56
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$7, %eax
	jg	.L56
	movl	$1, %eax
	jmp	.L53
.L56:
	movl	$0, %eax
.L53:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4882:
	.size	parse_move, .-parse_move
	.section	.rodata
.LC1:
	.string	"Checkers SDL"
	.align 8
.LC2:
	.string	"/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
.LC3:
	.string	"Failed to load font!"
.LC4:
	.string	"Invalid move: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4883:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$32, %edi
	call	SDL_Init@PLT
	call	TTF_Init@PLT
	movl	$0, %r9d
	movl	$720, %r8d
	movl	$720, %ecx
	movl	$805240832, %edx
	movl	$805240832, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	SDL_CreateWindow@PLT
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movl	$2, %edx
	movl	$-1, %esi
	movq	%rax, %rdi
	call	SDL_CreateRenderer@PLT
	movq	%rax, -80(%rbp)
	movl	$24, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	TTF_OpenFont@PLT
	movq	%rax, -72(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L59
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L75
.L59:
	movl	$0, %eax
	call	init_board
	movl	$1, -96(%rbp)
	jmp	.L61
.L73:
	movl	-64(%rbp), %eax
	cmpl	$256, %eax
	jne	.L63
	movl	$0, -96(%rbp)
	jmp	.L62
.L63:
	movl	-64(%rbp), %eax
	cmpl	$768, %eax
	jne	.L62
	movl	-44(%rbp), %eax
	movl	%eax, -92(%rbp)
	cmpl	$13, -92(%rbp)
	jne	.L65
	movl	input_pos(%rip), %eax
	cmpl	$4, %eax
	jne	.L65
	leaq	-100(%rbp), %rsi
	leaq	-104(%rbp), %rcx
	leaq	-108(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	leaq	input(%rip), %rax
	movq	%rax, %rdi
	call	parse_move
	testl	%eax, %eax
	je	.L66
	movl	-108(%rbp), %edx
	movl	-112(%rbp), %eax
	cltq
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rax, %rdx
	leaq	board(%rip), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movzbl	current_player(%rip), %eax
	cmpb	%al, %dl
	jne	.L66
	movzbl	current_player(%rip), %eax
	movsbl	%al, %edi
	movl	-100(%rbp), %ecx
	movl	-104(%rbp), %edx
	movl	-108(%rbp), %esi
	movl	-112(%rbp), %eax
	movl	%edi, %r8d
	movl	%eax, %edi
	call	make_move
	jmp	.L67
.L66:
	leaq	input(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L67:
	movl	$0, input_pos(%rip)
	movb	$0, input(%rip)
	jmp	.L62
.L65:
	cmpl	$8, -92(%rbp)
	jne	.L68
	movl	input_pos(%rip), %eax
	testl	%eax, %eax
	jle	.L68
	movl	input_pos(%rip), %eax
	subl	$1, %eax
	movl	%eax, input_pos(%rip)
	movl	input_pos(%rip), %eax
	cltq
	leaq	input(%rip), %rdx
	movb	$0, (%rax,%rdx)
	jmp	.L62
.L68:
	movl	input_pos(%rip), %eax
	cmpl	$3, %eax
	jg	.L62
	cmpl	$96, -92(%rbp)
	jle	.L69
	cmpl	$122, -92(%rbp)
	jle	.L70
.L69:
	cmpl	$47, -92(%rbp)
	jle	.L62
	cmpl	$57, -92(%rbp)
	jg	.L62
.L70:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-92(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L71
	movl	-92(%rbp), %eax
	movl	%eax, %edi
	call	toupper@PLT
	movl	%eax, %ecx
	jmp	.L72
.L71:
	movl	-92(%rbp), %eax
	movl	%eax, %ecx
.L72:
	movl	input_pos(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, input_pos(%rip)
	cltq
	leaq	input(%rip), %rdx
	movb	%cl, (%rax,%rdx)
	movl	input_pos(%rip), %eax
	cltq
	leaq	input(%rip), %rdx
	movb	$0, (%rax,%rdx)
.L62:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_PollEvent@PLT
	testl	%eax, %eax
	jne	.L73
	movq	-72(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	draw_board
	movl	$16, %edi
	call	SDL_Delay@PLT
.L61:
	cmpl	$0, -96(%rbp)
	jne	.L62
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	TTF_CloseFont@PLT
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyRenderer@PLT
	movq	-88(%rbp), %rax
	movq	%rax, %rdi
	call	SDL_DestroyWindow@PLT
	call	TTF_Quit@PLT
	call	SDL_Quit@PLT
	movl	$0, %eax
.L75:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L76
	call	__stack_chk_fail@PLT
.L76:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4883:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
