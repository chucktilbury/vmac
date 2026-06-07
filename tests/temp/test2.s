	.text
	.file	"test2.c"
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
	cmpl	$1, -8(%rbp)
	jne	.LBB0_2
# %bb.1:
	callq	func1
	jmp	.LBB0_11
.LBB0_2:
	cmpl	$2, -8(%rbp)
	jne	.LBB0_4
# %bb.3:
	callq	func2
	jmp	.LBB0_10
.LBB0_4:
	cmpl	$3, -8(%rbp)
	jne	.LBB0_6
# %bb.5:
	callq	func3
	jmp	.LBB0_9
.LBB0_6:
	cmpl	$4, -8(%rbp)
	jne	.LBB0_8
# %bb.7:
	callq	func4
.LBB0_8:
	jmp	.LBB0_9
.LBB0_9:
	jmp	.LBB0_10
.LBB0_10:
	jmp	.LBB0_11
.LBB0_11:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
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
.Lfunc_end3:
	.size	func3, .Lfunc_end3-func3
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
.Lfunc_end4:
	.size	func4, .Lfunc_end4-func4
	.cfi_endproc
                                        # -- End function
	.ident	"Debian clang version 19.1.7 (3+b1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym func1
	.addrsig_sym func2
	.addrsig_sym func3
	.addrsig_sym func4
