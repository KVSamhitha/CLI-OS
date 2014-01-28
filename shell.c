#include <stdio.h>

char PATH[1024] = "bin/:temp/";

void show_prompt() {
	printf("\nSB_Unix>");
	//ls();
//	ps();
}


//Concatenate str1 and str2
//Add str2 to str1

char* strcat_x(char* str1,char* str2) {
        int i = 0,j = 0;

        if((str1 == NULL) || (str2 == NULL))
                return NULL;

        while(str1[++i] != '\0');

        while( (str1[i++] =  str2[j++]) != '\0')

        str1[i] = '\0';

        return str1;
}



/*
 * Copy src string to dest string and null terminate
 * Return 0 on success. 1 on failure
 *
 */

unsigned char strncpy(char* dest,const char* src,int count) {

        if((src == NULL) || (dest == NULL) )
                return 0;

        int i = 0;

	for(i = 0 ; i < count; i++) {
		dest[i] = src[i];
	}

        dest[i] = '\0';

        return 1;
}


unsigned char strcmp_x(const char* str1, const char* str2) {

        int i = 0;

        if((str1 == NULL) || (str2 == NULL))
                return 0;

        while(str1[i] == str2[i]) {

                if(str1[i] == '\0')
                        return 1;
                i++;
        }


	return 0;
}

int main(int argt, char* argvnum[],char* envp[]) {

	char tempbuf[256];


	//printf("argt is %x\n",argt);
	volatile int run_shell = 1;
	

	while(run_shell == 1) {
		// Show prompt and read from the user
		show_prompt();
		scanf("%s",tempbuf);
		

						//printf("File exists!!\n");
						volatile uint16_t val = fork();
						if(val == 0)
							execvpe(tempbuf,0,NULL);	
						else {
							uint64_t i=0;
							while(i<100000000)
								i++;
						}
							//sleep(10);
							//waitpid(val);
	}
	return 0;
}
