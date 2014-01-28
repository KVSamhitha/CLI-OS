#include<syscall.h>
#include"../sys/fs.h"

struct dirent * readdir(struct dir_struct * dir) {
	uint64_t * param = (uint64_t *)0xfffffe0000000000;
	param[0] = (uint64_t)dir;
	__syscall1(9,(uint64_t)dir);	
	return ((struct dirent *)param[0]);
}
