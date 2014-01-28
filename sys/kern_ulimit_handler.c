#include <function.h>
#include<defs.h>
#include<structs.h>
#include<stdio.h>
#include "fs.h"
extern void kern_ulimit(uint64_t);

void kern_ulimit_handler()
{
	uint64_t * fd = (uint64_t *)0xfffffe0000000000;
	kern_ulimit((uint64_t)fd[0]);
}
