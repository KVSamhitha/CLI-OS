#include<function.h>
#include<structs.h>
extern struct task_struct * current_task;
extern void map_user_page_virtual(uint64_t *, uint64_t, uint64_t, uint16_t, int);
extern uint64_t * get_free_page();

extern void create_new_page_for_child(uint64_t * ,uint64_t, int);
extern void change_page_perm(uint64_t * ,uint64_t ,int );
extern void kern_exit_handler();

void page_fault_isr_handler () {
	//print_out("    TRIPPLE FAULT OCCURED IN TASK %d WITH ERROR CODE %x   ",current_task->task_id,**error_code);
	uint64_t free;
	uint64_t ulimit_start;
	uint64_t ulimit_end;
	uint64_t * virtual_addr;
	uint16_t parent = current_task->task_parent_id;
	uint16_t child;
	__asm__ volatile("movq %%cr2, %0"
        	: "=b" (virtual_addr)
                :
                );
	
	if((uint64_t)virtual_addr == (uint64_t)0x0000) {
		print_out(" \nSEGV FAULT...KILLING PROCESS\n");
		kern_exit_handler();
	}
	switch (**error_code) {
		case 1 : print_out("      Supervisor mode Protection Violation          ");
			 break;

		case 2 : //print_out("      Supervisor mode Write fault        ");
			 __asm__ volatile("movq %%cr2, %0"
                        	: "=b" (virtual_addr)
                        	: 
                		);
			 	free = (uint64_t)get_free_page();
			 	map_page_virtual((uint64_t *)virtual_physfree,(uint64_t)virtual_addr,free,1,7);	
			 	map_user_page_virtual((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,free,1,7);
			 break;

		case 3 : print_out("      Supervisor mode Protection and Write fault      ");
			 break;

		case 4 : //print_out("      User mode fault      ");
			 __asm__ volatile("movq %%cr2, %0"
                                : "=b" (virtual_addr)
                                :
                                );
			 //print_out("   The faulting address is %x   ",virtual_addr);
			 ulimit_start = (uint64_t)current_task->ulimit_top;
			 ulimit_end = (uint64_t)current_task->ulimit;
			 if(((uint64_t)virtual_addr >= ulimit_end) && ((uint64_t)virtual_addr <= ulimit_start)) {
					print_out("\n The user stack limit has been exceeded, hence killing process\n ");
					kern_exit_handler();
			 } 
			 
			 free = (uint64_t)get_free_page();
			 map_user_page_virtual((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,free,1,7);
			 break;

		case 5 : print_out("      User mode Protection violation       ");
			 __asm__ volatile("movq %%cr2, %0"
                                : "=b" (virtual_addr)
                                :
                                );
                         print_out("the faulting address is  %p     ",virtual_addr); 
			 break;

		case 6 : //print_out("      User mode Write violation       ");
                         __asm__ volatile("movq %%cr2, %0"
                                : "=b" (virtual_addr)
                                :
                                );
                         ulimit_start = (uint64_t)current_task->ulimit_top;
                         ulimit_end = (uint64_t)current_task->ulimit;
                         if(((uint64_t)virtual_addr >= ulimit_end) && ((uint64_t)virtual_addr <= ulimit_start)) {
                                        print_out("\n The user stack limit has been exceeded, hence killing process\n ");
                                        kern_exit_handler();
                         }
                         free = (uint64_t)get_free_page();
                         //print_out("mapping %p to %x on request of task with id %d    ",virtual_addr,free,current_task->task_id);
			 map_user_page_virtual((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,free,1,7);
			break;

		default : //print_out("     Fault due to RSVD or I/D        ");
			  __asm__ volatile("movq %%cr2, %0"
                                : "=b" (virtual_addr)
                                :
                                );
			  //print_out("The faulting address is %x  ",virtual_addr);
			  if ((current_task->task_parent_id == 0 && current_task->ref_count == 0) || (current_task->task_parent_id != 0 && task[parent].ref_count == 0)) {
				change_page_perm((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,7);
			  }
			  else {
				//print_out(" There is dependency  ");
				if(current_task->task_parent_id == 0) {
					//print_out("  its the parent trying to write  ");
					change_page_perm((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,7);
					int i;
					for(i=0;i<10;i++) {
						if(current_task->child[i] == 20)
							break;
						else {	
							child = current_task->child[i];
							//print_out(" The child chosen for update is %d ",child);
							create_new_page_for_child((uint64_t *)task[child].virtual_cr3,(uint64_t)virtual_addr,7);
						}
					}			
				}
				else {
					//print_out(" its the child requesting to write  ");
					change_page_perm((uint64_t *)task[parent].virtual_cr3,(uint64_t)virtual_addr,7);
					create_new_page_for_child((uint64_t *)current_task->virtual_cr3,(uint64_t)virtual_addr,7);
				}
			  }
			  break;
	}	
}
