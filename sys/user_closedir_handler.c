#include <function.h>
#include<defs.h>
#include<structs.h>
#include<stdio.h>
#include "fs.h"

void user_closedir_handler()
{
	uint64_t * fd = (uint64_t *)0xfffffe0000000000;
	int * fd_int = (int *)0xfffffe0000000000;
	fd_int[0] = (int)kern_closedir((struct dir_struct *)fd[0]);
}
