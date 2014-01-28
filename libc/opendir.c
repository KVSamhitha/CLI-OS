#include<syscall.h>

struct dir_struct * opendir(const char * filename) {
	uint64_t * file_name = (uint64_t *)0xfffffe0000000000;
	file_name[0] = (uint64_t)filename;
	__syscall1(8,(uint64_t)filename);	
	return ((struct dir_struct *)file_name[0]);
}
