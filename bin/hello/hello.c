#include <stdio.h>

int main(int argc, char* argv[]) {
	int * d = (int *)malloc(1000);
	char * name = (char *)malloc(10);
	printf("\nHello World!\n");

	printf("\nENTER YOUR NAME : ");
	scanf("%s",name);
	printf("\nThe entered name is %s",name);

	printf("\nENTER A DIGIT :");
	scanf("%d",d);
	printf("\nThe entered digit is %d",*d);
	

	printf("\nI am going to sleep for 3 seconds\n");
	sleep(3);

	printf("\n I will get my pid now\n");
	uint16_t pid = getpid();
	printf("\nMy pid is %d\n",pid);

	return 0;
}
