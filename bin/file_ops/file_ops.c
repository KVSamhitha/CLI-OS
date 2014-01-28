#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("Hello OS!\n");

		uint16_t pid = getpid();
		printf(" \nI am the child with pid %d ",pid);
		printf("\nI AM OPENING A FILE!! ");
		int fd = open("temp/abc");
		printf(" The return value of opening temp/abc is %d  ",fd);
		printf(" I am going to sleep for 2 seconds ");
		sleep(2);
		fd = open("temp/def");
		printf(" The return value of opening temp/def is %d  ",fd);
		char * buf = malloc(100);

		int succ = read(fd,buf,10);
		buf[succ] = '\0';
		printf(" \n--the num of bytes read is %d and the contents are %s  ",succ,buf);	
		
		succ = read(fd,buf,9);
		buf[succ] = '\0';
		printf(" \nthe num of bytes read is %d and the contents are %s  ",succ,buf);	

		succ = read(fd,buf,100);
		buf[succ] = '\0';
		printf(" \nthe num of bytes read is %d and the contents are %s  ",succ,buf);	
		succ = close(fd);
		printf(" \nThe close was a success with value %d ",succ);
		succ = close(10);
		printf(" \nNow is dont know which this is..%d ",succ);

		struct dir_struct * ptr;
        	struct dirent * dirent_ptr;
        	ptr = opendir("bin/");
        	if(ptr != NULL) {
                	printf("\nname is %s ",ptr->d_name);

                while((dirent_ptr = readdir(ptr)) != NULL)
                        printf(" %s ",dirent_ptr->d_name);
                int ret = closedir(ptr);
                printf("  the return value is %d ",ret);
        	}
        	else
                	printf(" Could not open directory ");

	return 0;
}
