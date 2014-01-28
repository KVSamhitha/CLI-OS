#include<syscall.h>

void cd(const char * dir_name) {
	uint64_t * file_name = (uint64_t *)0xfffffe0000000000;
	file_name[0] = (uint64_t)dir_name;
	__syscall1(11,(uint64_t)dir_name);	
//	return ((int)file_name[0]);
}
