#include <function.h>
#include<defs.h>
#include<structs.h>
#include<stdio.h>
#include "fs.h"

void user_readdir_handler()
{
	uint64_t * param = (uint64_t *)0xfffffe0000000000;
	param[0] = (uint64_t)kern_readdir((struct dir_struct *)param[0]);
}
