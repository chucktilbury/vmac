	.text
	.file	"test1.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	decl	%eax
	movl	%eax, %ecx
	movq	%rcx, -16(%rbp)                 # 8-byte Spill
	subl	$3, %eax
	ja	.LBB0_5
# %bb.6:
	movq	-16(%rbp), %rax                 # 8-byte Reload
	leaq	.LJTI0_0(%rip), %rcx
	movslq	(%rcx,%rax,4), %rax
	addq	%rcx, %rax
	jmpq	*%rax
.LBB0_1:
	callq	func1
	jmp	.LBB0_5
.LBB0_2:
	callq	func2
	callq	ofunc
	jmp	.LBB0_5
.LBB0_3:
	callq	func3
	jmp	.LBB0_5
.LBB0_4:
	callq	func4
.LBB0_5:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
	.section	.rodata,"a",@progbits
	.p2align	2, 0x0
.LJTI0_0:
	.long	.LBB0_1-.LJTI0_0
	.long	.LBB0_2-.LJTI0_0
	.long	.LBB0_3-.LJTI0_0
	.long	.LBB0_4-.LJTI0_0
                                        # -- End function
	.text
	.p2align	4, 0x90                         # -- Begin function func1
	.type	func1,@function
func1:                                  # @func1
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	func1, .Lfunc_end1-func1
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function func2
	.type	func2,@function
func2:                                  # @func2
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	func2, .Lfunc_end2-func2
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function ofunc
	.type	ofunc,@function
ofunc:                                  # @ofunc
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end3:
	.size	ofunc, .Lfunc_end3-ofunc
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function func3
	.type	func3,@function
func3:                                  # @func3
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end4:
	.size	func3, .Lfunc_end4-func3
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90                         # -- Begin function func4
	.type	func4,@function
func4:                                  # @func4
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end5:
	.size	func4, .Lfunc_end5-func4
	.cfi_endproc
                                        # -- End function
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym func1
	.addrsig_sym func2
	.addrsig_sym ofunc
	.addrsig_sym func3
	.addrsig_sym func4
