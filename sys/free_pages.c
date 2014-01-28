#include <defs.h>
#include<function.h>
#include<structs.h>

char * free_bitmap = (char *)0xffffffff80400000;
extern struct task_struct * current_task;
extern uint64_t * virtual_physfree;

void initialize_free_pages() {
	int no_of_pages = (total * 1048576) / 4096; 		
	//print_out(" The total number of pages required is %d",no_of_pages);
	uint16_t i;
	for(i = 0; i < no_of_pages; i++) {
		free_bitmap[i] = 1;
	}
	for(i=0; i<20; i++) {
		kmalloc_free_ptr[i] = 0;
		stack_free_ptr[i] = 0;
	}
	//print_out("    Address of free_bitmap is %p",free_bitmap); 
	/*
	uint32_t address = 0; 
	uint16_t page_no;
	for(address = 0;address < 0xa00000;) {
		page_no = address / 0x10000;
		free_bitmap[page_no] = 0;
		address += 0x1000;
	}
	*/
}
uint64_t * get_free_page() {
	uint64_t * page_addr = (uint64_t *) 0x00000;
	uint64_t temp = 0;
	int no_of_pages = (total * 1048576) / 4096, free_page = 0; 		
	//print_out(" the number of pages is %d and total is %d",no_of_pages,total);
	for(free_page = 2816; free_page < no_of_pages; free_page++) {
		if(free_bitmap[free_page] == 1) {
			temp = free_page * 0x1000;
			page_addr = (uint64_t *)temp;
			//print_out(" The first page that is free is %x and the free_page offset is at %d", page_addr,free_page);
			free_bitmap[free_page] = 0;
			break;
		}
	}
	return page_addr;
}	
uint64_t * get_free_page_for_paging() {
	uint64_t * page_addr = (uint64_t *) 0x00000;
	uint64_t temp = 0;
	//int no_of_pages = (total * 1048576) / 4096, free_page = 0; 		
	int free_page = 0;
	//print_out(" the number of pages is %d and total is %d",no_of_pages,total);
	for(free_page = 0; free_page < 1280; free_page++) {
		if(free_bitmap[free_page] == 1) {
			temp = free_page * 0x1000;
			page_addr = (uint64_t *)temp;
			//print_out(" The first page that is free is %x and the free_page offset is at %d", page_addr,free_page);
			free_bitmap[free_page] = 0;
			break;
		}
	}
	return page_addr;
}	

uint64_t * get_free_page_for_tasks() {
        uint64_t * page_addr = (uint64_t *) 0x00000;
        uint64_t temp = 0;
        //int no_of_pages = (total * 1048576) / 4096, free_page = 0;            
        int free_page = 0;
        //print_out(" the number of pages is %d and total is %d",no_of_pages,total);
        for(free_page = 1280; free_page < 2304; free_page++) {
                if(free_bitmap[free_page] == 1) {
                        temp = free_page * 0x1000;
                        page_addr = (uint64_t *)temp;
                        //print_out(" The first page that is free is %x and the free_page offset is at %d", page_addr,free_page);
                        free_bitmap[free_page] = 0;
                        break;
                }
        }
        return page_addr;
}

void free_page(uint64_t page) {
	int page_no = page / 4096;
	//print_out("     the page that will be freed is %d     ", page_no);
	free_bitmap[page_no] = 1;
} 

uint64_t * get_free_page_for_stack() {
        uint64_t * page_addr = (uint64_t *) 0x00000;
        uint64_t temp = 0, vbase = (uint64_t)0xffffffff80000000;
        //int no_of_pages = (total * 1048576) / 4096, free_page = 0;
        int free_page = 0;
        //print_out(" the number of pages is %d and total is %d",no_of_pages,total);
        for(free_page = 2304; free_page < 2560; free_page++) {
                if(free_bitmap[free_page] == 1) {
                        temp = free_page * 0x1000;
                        temp = vbase | temp;
                        page_addr = (uint64_t *)temp;
                        //print_out(" The first page that is free is %x and the free_page offset is at %d", page_addr,free_page);
                        free_bitmap[free_page] = 0;
                        break;
                }
        }
        return page_addr;
}

uint64_t * get_free_kmalloc_page() {
        uint64_t * page_addr = (uint64_t *) 0x00000;
        uint64_t temp = 0, vbase = (uint64_t)0xffffffff80000000;
        //int no_of_pages = (total * 1048576) / 4096, free_page = 0;
	int free_page = 0;
        //print_out(" the number of pages is %d and total is %d",no_of_pages,total);
        for(free_page = 2560; free_page < 2816; free_page++) {
                if(free_bitmap[free_page] == 1) {
                        temp = free_page * 0x1000;
			temp = vbase | temp;
                        page_addr = (uint64_t *)temp;
                        //print_out(" The first page that is free is %x and the free_page offset is at %d", page_addr,free_page);
                        free_bitmap[free_page] = 0;
                        break;
                }
        }
        return page_addr;
}
void free_kmalloc_page(uint16_t pid) {
	uint64_t kmalloc_base = kmalloc_free_ptr[pid] & (uint64_t)0x0000000000fff000;
	kmalloc_base = kmalloc_base >> 12;
	//print_out("    The Kmalloc base is %d   ",kmalloc_base);
	kmalloc_free_ptr[pid] = 0;
	free_bitmap[kmalloc_base] = 1;	
	//int page_no = page / 4096;
	//print_out("     the page that will be freed is %d     ", page_no);
	//free_bitmap[page_no] = 1;
} 
/*
void free_stack_page(uint16_t pid) {
        uint64_t stack_base = stack_free_ptr[pid] & (uint64_t)0x0000000000fff000;
        stack_base = stack_base >> 12;
        //print_out("    The Kmalloc base is %d   ",kmalloc_base);
        stack_free_ptr[pid] = 0;
        free_bitmap[stack_base] = 1;
        //int page_no = page / 4096;
        //print_out("     the page that will be freed is %d     ", page_no);
        //free_bitmap[page_no] = 1;
}
*/
void free_stack_page(uint16_t pid) {
	uint64_t page = (uint64_t)task[pid].task_kstack;
	page = page & (uint64_t)0x000000000fffffff;
	free_page(page);
	page = (uint64_t)task[pid].task_ustack;
	page = page & (uint64_t)0x000000000fffffff;
	free_page(page);
	page = (uint64_t)task[pid].ulimit;
	page = page & (uint64_t)0x000000000fffffff;
	free_page(page);
}
void free_paging_structures(uint64_t * pml4e_ptr) {
	uint64_t * pdptr_table;
	uint64_t * pd_table;
	uint64_t * pg_table;
	uint64_t address;
	int pml4e_offset = 0;
	int pdptr_offset = 0;
	int pd_offset = 0;
	int pg_offset = 0;
	//int pml4e_empty = 0;
	//int pdptr_empty = 0;
	//int pd_empty = 0;
	//int pg_empty = 0;
	//uint64_t pml4e_address;
	//uint64_t pdptr_address;
	//uint64_t pd_address;
	//uint64_t pg_address;
	int pg_no;
	//print_out(" the virtual cr3 is %x ",pml4e_ptr);
	for(pml4e_offset = 0; pml4e_offset < 512; pml4e_offset++) {
		if(pml4e_offset != 510) {
		if(pml4e_ptr[pml4e_offset] != 0) {
			address = ((uint64_t) pml4e_ptr[pml4e_offset]) >> 12;
                        address = address << 12;
			pg_no = address / 4096;
			//print_out(" pml4e_offset %d - %x ",pml4e_offset,address);
			free_bitmap[pg_no] = 1;
                        address = address | (uint64_t)0xffffffff80000000;
                        pdptr_table = ((uint64_t *) address);			
			for(pdptr_offset = 0;pdptr_offset < 512; pdptr_offset++) {
				if(pdptr_table[pdptr_offset] != 0) {
					address = ((uint64_t) pdptr_table[pdptr_offset]) >> 12;
                        		address = address << 12;
					pg_no = address / 4096;
					//print_out(" pdptr_offset %d - %x ",pdptr_offset,address);
					free_bitmap[pg_no] = 1;
                        		address = address | (uint64_t)0xffffffff80000000;
                        		pd_table = ((uint64_t *) address);
					for(pd_offset = 0;pd_offset < 512; pd_offset++) {
						if(pd_table[pd_offset] != 0) {
							address = ((uint64_t) pd_table[pd_offset]) >> 12;
                                        		address = address << 12;
							pg_no = address / 4096;
							//print_out(" pd_offset %d - %x ",pd_offset,address);
							free_bitmap[pg_no] = 1;
                                        		address = address | (uint64_t)0xffffffff80000000;
                                        		pg_table = ((uint64_t *) address);
							for(pg_offset=0; pg_offset<512; pg_offset++) {
								if(pg_table[pg_offset] != 0) {
									address = ((uint64_t) pg_table[pg_offset]) >> 12;
                                                        		address = address << 12;
									if(address >= 0xb00000) {	
										pg_no = address / 4096;
										//print_out(" pg_offset %d - %x ",pg_offset,address);
										free_bitmap[pg_no] = 1;
									}
								}
							}
						}
					}
				}		
			}
		}
	}
	}
	//address = (uint64_t)pml4e_ptr & (uint64_t)0x000000000fffffff;
	//pg_no = address /4096;
	//print_out(" pml4e_address = %x, pg_no = %d  ",address,pg_no);
	//free_bitmap[pg_no] = 1;
}
