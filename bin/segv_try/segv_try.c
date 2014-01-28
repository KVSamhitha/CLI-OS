#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("\n**********I am the result of exec**********\n");
	char * chr = (char *)0x0000000000000000;
	chr[0]= 'c';
	printf("\nthe char at address 0 is %c",chr[0]);
	return 0;
}
