#include<syscall.h>
#include<stdio.h>
void execvpe(const char * filename, int argc, char * argv[]) {
	//printf("-------- the arguments are %s and %s-------",argv[0],argv[1]);
	int * no_of_arg = (int *)0xffffffff809ff000;
	no_of_arg[0] = argc;
	if(argc > 0 && argv != NULL) {
		char * arguments = (char *)0xffffffff809ff00a;
		//printf("\n argc is %d\n",no_of_arg[0]);	
		int i=0,j;
		for(i=0;i<argc;i++) {
			j=0;
			while(*argv[i] != '\0') {
				arguments[j] = *argv[i];
				j++;
				argv[i]++;
			}
			arguments[j] = '\0';
			//printf("\n the argument is %s ",arguments);
			arguments+=50;
		}
	}
	char * file_name = (char *)0xfffffe0000000000;
	while(*filename != '\0') {
		*file_name = *filename;
		filename++;
		file_name++;
	}
	*file_name = '\0';
        __syscall1(6,(uint64_t)file_name[0]);
}
