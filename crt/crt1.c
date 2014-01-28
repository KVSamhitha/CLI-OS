#include <stdlib.h>

void _start() {
	char * args = (char *)0xffffffff809ff000;
	int argc = (int)(*args);
	args += 10;
	char* argv[10];
	argv[0] = (char *)args;
	args += 50;
	argv[1] = (char *)args;
	args += 50;
	argv[2] = (char *)args;
	args += 50;
	argv[3] = (char *)args;
	char* envp[10];
	int res;
	res = main(argc, argv, envp);
	exit(res);
}
