#include <function.h>
#include<defs.h>
#include<structs.h>

extern void free_stack_page(uint16_t);
extern void free_kmalloc_page(uint16_t);
extern struct task_struct * current_task;
extern uint64_t waitid;

void dummy_wait() {
}
void kern_wait_handler()
{
	//print_out(" In kern_wait handler!! ");	
	int i=0; //, waitflag = 0;
	for(i=0;i<10;i++) {
		if(current_task->child[i] != 20) {
			current_task->waitid = current_task->child[i];
			break;
		}
	}
	if(current_task->waitid == 20) {
		for(i=0;i<10;i++) {
			if(current_task->exec_child[i] != 20) {
				current_task->waitid = current_task->exec_child[i];
				break;
			}
		}
	}
	if(current_task->waitid != 20) {
		//print_out(" task.waitid of %d is now set to %d  ",current_task->task_id,current_task->waitid);
        	current_task->state = WAITING;
		__asm__ volatile(
			"sti;"
			: : :"memory"
		);
		//while(i<10000000000) {
		while(current_task->waitid != 20) {
			dummy_wait();
			//i++;
		}	
	}
}
