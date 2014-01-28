#include <function.h>
#include<defs.h>
#include<structs.h>
#include<stdio.h>
#include"fs.h"

void kern_cd_handler()
{
	uint64_t * filename = (uint64_t *)0xfffffe0000000000;
	//print_out(" the dir name is %s ",(char *)filename[0]);
	kern_cd((char *)filename[0]);
}
