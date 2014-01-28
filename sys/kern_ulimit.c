#include <function.h>
extern int ulimit;

void kern_ulimit(uint64_t value){
	print_out("\nThe ulimit value is set to %d\n",value);
	ulimit = value;
}
