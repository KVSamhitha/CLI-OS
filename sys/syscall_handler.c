#include <function.h>
#include<defs.h>
#include<structs.h>
#include "fs.h"

extern void free_stack_page(uint16_t);
extern void free_kmalloc_page(uint16_t);
extern struct task_struct * current_task;
extern void func3();
extern void kern_ls();
extern void kern_ps();

void syscall_handler()
{
	int function_num;

	__asm__ volatile (
			"mov %%eax,%0;"
			: "=r"(function_num) 
			: 
	);
	
	//print_out("function number is %d\n",function_num);
	switch(function_num) {	
		case 0x80: kern_ls();
			   break;
		case 0x90: kern_ps();
			   break;
		default:
			break;
	}
}
