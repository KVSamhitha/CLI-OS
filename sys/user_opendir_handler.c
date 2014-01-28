#include <function.h>
#include<defs.h>
#include<structs.h>
#include<stdio.h>
#include"fs.h"

struct dir_struct * user_opendir_handler()
{
	uint64_t * filename = (uint64_t *)0xfffffe0000000000;
	//print_out(" the file name is %s ",(char *)filename[0]);
	filename[0] = (uint64_t)kern_opendir((char *)filename[0]);
	//print_out(" The return value is %d ",filename[0]);
	return ((struct dir_struct *)filename[0]);
}
