#include<syscall.h>
#include<stdio.h>

void  ulimit(uint64_t size) {
	//int ret_val = 0;
	uint64_t *page_ptr  = (uint64_t *)0xfffffe0000000000;
	page_ptr[0] = (uint64_t)size;

	if(size > 4096) {
		printf("\n The given ULIMIT is greater than the maximum limit of 4096 bytes\n");
		return;
	}
        __syscall1(12,size);

}
