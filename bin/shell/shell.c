#include <stdio.h>

char PATH[1024] = "bin/";

void show_prompt() {
	printf("\nSB_Unix>");
}


uint64_t atoi_u( char* num_string, int base) {

        int last_index = 0;
        int dec_factor = 1;
        uint64_t num = 0;
        uint64_t multiplier = 1 ;
        char ch;

        while(num_string[last_index+1] != '\0') {
                last_index++;
        }

        int i = 0;
        for(i =0 ; i <= last_index; i++) {
                ch = num_string[i];
                if(base == 10) {
                        // Check for a valid decimal number..
                        if(ch < '0' || ch > '9')
                                return -1;
                }
                if(base == 16) {
                        // Check for a valid hex number
                        if(!( (ch >= 'a' && ch <= 'f')  || (ch >= 'A' && ch <= 'F') || (ch >= '0' && ch <= '9') ))
                                return -1;
                }

        }

        while(last_index != -1) {
                ch = num_string[last_index];
                if(base == 16) {
                        if(ch >= '0' && ch <= '9') {
                                multiplier = ch - '0';
                        }
                         else if(ch >= 'a' && ch <= 'f') {
                                multiplier = 10 + ch - 'a';
                        }
                        else
                        {
                                multiplier = 10 + ch - 'A';
                        }
                }
                if((base == 10) || (base == 8)) {
                        multiplier = ch - '0';
                }

                //num = num + dec_factor * (num_string[last_index] - '0' );
                num = num + dec_factor * multiplier;
                dec_factor *= base;
                last_index--;
        }
        return num;

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


/*
void do_extra() {

	volatile char* shared_page = (char*) 0xffffffff809ff800;
	shared_page += 10;
	//int * lines_ptr = (int*)0xffffffff809ff800;
	int * lines_ptr = (int*)0xffffffff809ff800;
	int num_lines = *lines_ptr;	

	while(num_lines != 0) {
		printf("%s ",shared_page);	
		shared_page += 50;		
		num_lines--;
	} 

}
*/

int main(int argt, char* argvnum[],char* envp[]) {

	char command_buf[256];
	char *argv[10];

	int i = 0;
	for(i = 0 ; i < 5; i++) {
		argv[i] = (char*)malloc(20);
	}

	//printf("argt is %x\n",argt);
	volatile int run_shell = 1;

	while(run_shell == 1) {
		// Show prompt and read from the user
		show_prompt();
		int argc = 0;


		//printf("argt is %x\n",argt);
		//Read the command from the user
		scanf("%s",command_buf);

		// Parse the input at the prompt and tokenize(space as token) it to get individual args.
		int index = 0,start_index = 0;
		//Strip leading spaces

		while(command_buf[index] != '\0') {
			// Parse command_buf and  put arguments into argv
			if(command_buf[index] == ' ') {
				if((index - start_index) > 0 ) {
					//printf("\nallocating %d bytes",index-start_index);
					//argv[argc++] = (char*)malloc((index-start_index) + 1);
					argc++;
					strncpy(argv[argc-1],command_buf+start_index,index-start_index);	
					start_index = index + 1;
				}
			}	
			index++;
		}

	if(index > 0) {
		//argv[argc++] = (char*)malloc((index-start_index) + 1);
		argc++;
		strncpy(argv[argc-1],command_buf+start_index,index-start_index);	
	}

	// Compare argv[0] to determine the file name..	
//	printf("argc is %d\n",argc);	
//	int temp;
//	for(temp = 0; temp < argc; temp++)
//		printf("%s\n",argv[temp]);

//	printf("argv[0] is %s\n",argv[0]);
	
//	printf("\n PATH is %s\n",PATH);
//	printf("argv[0] is %s\n",argv[0]); 

	if(strcmp_x(argv[0],"cd")) {
           // printf("\ndo cd\n");
	    cd(argv[1]);
	    continue;
        }
        else if (strcmp_x(argv[0],"ulimit")) {
           //printf("\ndo ulimit\n");
	   ulimit(atoi_u(argv[1],10));
		continue;
        }



	if(index > 0) {
		index = 0,start_index = 0;
		char tempbuf[64];
		while(PATH[index] != '\0') {
			if(PATH[index] == ':') {
				if(index - start_index > 0) {
					strncpy(tempbuf,PATH+start_index,index-start_index);
					strcat_x(tempbuf,argv[0]);
					start_index = index + 1;
						 int fd;
						fd = open(tempbuf);
						if(fd > 0) { 
							//int flag = 0;
							//printf("File exists!!\n");
							//if(strcmp_x(argv[0],"sh")) {
							//	flag = 1;
							//}
							
							volatile uint16_t val = fork();
							if(val == 0)
								execvpe(tempbuf,argc,argv);	
							else {
								waitpid(val);
							}
						}
						else { 
							printf("\nCommand not found\n");
							break;
						}
						close(fd);
						if(fd > 0)
							break;
				}
			}
			index++;
		}
		if((start_index == 0) && ( index > 0)) {
			strncpy(tempbuf,PATH+start_index,index-start_index);
	                strcat_x(tempbuf,argv[0]);
			//printf("start_index is %d\n",start_index);
                        //printf("-------tempbuf is %s\n",tempbuf);
			int fd;
			fd = open(tempbuf);
			if(fd > 0) {
				//printf("------File exists!!\n");
				//int flag = 0;	
			       	//if(strcmp_x(argv[0],"sh")) {
				//	flag = 1;
				//  }

                                volatile uint16_t val = fork();
                                if(val == 0)
                                    execvpe(tempbuf,argc,argv);
                                else {
                                    waitpid(val);

                                }

			}
			else 
                            printf("\nCommand not found\n");
			close(fd);

		}
	}
		
	}


// strcmp to check if the command is valid
// if yes, then execute

//	printf("%s",command_buf);
	return 0;
}
