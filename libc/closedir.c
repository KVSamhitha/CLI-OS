#include<syscall.h>
#include"../sys/fs.h"

int closedir(struct dir_struct * dir) {
	uint64_t * file_desc = (uint64_t *)0xfffffe0000000000;
	file_desc[0] = (uint64_t)dir;
	__syscall1(10,(uint64_t)file_desc[0]);	
	return ((int)file_desc[0]);
}
