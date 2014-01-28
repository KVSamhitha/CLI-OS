#include <function.h>
#include <structs.h>


extern struct task_struct task[];


void kern_ps() {
	int i =0;
	
	print_out("\nName               PID    STATE\n");		

	for(i = 0; i <= 10; i++) {
		if((task[i].state != 4 ) && (task[i].state != 0) ) {
			print_out("%s            %d    ",task[i].func_name,task[i].task_id);
			switch(task[i].state) {
				case 1: print_out("RUNNING\n");
					break;
				case 2: print_out("WAITING\n");
					break;
				case 3: print_out("SUSPEND\n");
					break;
				case 5: print_out("SLEEP\n");
					break;
				case 6: print_out("EXIT_WAIT\n");
					break;
			}
		}	
	}
	
}
