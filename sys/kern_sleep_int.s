.extern kern_sleep_handler 

.global kern_sleep_int


kern_sleep_int:
	cli
#        push %rsp
#        movq %rsp,error_code
	push %rax
        push %rbx
        push %rcx
        push %rdx
        push %rsi
        push %rdi
	push %r8
        push %r9
	push %r10
	push %r11
	push %r12
	push %r13
	push %r14
	push %r15

	call kern_sleep_handler

	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %r11
	pop %r10	
	pop %r9
	pop %r8
        pop %rdi
        pop %rsi
	pop %rdx
        pop %rcx
        pop %rbx
	pop %rax

#	pop %rsp
#	pop %r11
	
#	pop %r10
 #       add $2,%r10
#	push %r10;
	
        sti

	iretq
