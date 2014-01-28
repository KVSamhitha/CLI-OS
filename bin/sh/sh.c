#include <stdio.h>


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




/*
 * Copy src string to dest string.
 * Return 0 on success. 1 on failure
 *
 */

unsigned char strcpy(char* dest,const char* src) {

        //if((src == NULL) || (dest == NULL) )
         //       return 0;

        int i = 0;

        while(src[i] != '\0') {
                dest[i] = src[i];
                i++;
        }

        dest[i] = '\0';

        return 1;
}


void execute(char* command) {
#if 0
// Parse the command into its arguments and execute.	
	int argcp = 0;
	
	char* argvp[5] ;
	int i = 0;
	for(i = 0 ; i < 5; i++) {
		argvp[i] = (char*) malloc(30);
	}
	int index = 0,start_index = 0;
                //Strip leading spaces

        while(command[index] != '\0') {
             // Parse command and  put arguments into argv
                        if(command[index] == ' ') {
                                if((index - start_index) > 0 ) {
                                        //printf("\nallocating %d bytes",index-start_index);
                                        //argv[argc++] = (char*)malloc((index-start_index) + 1);
                                        argcp++;
                                        strncpy(argvp[argcp-1],command+start_index,index-start_index);
                                        start_index = index + 1;
                                }
                        }
                        index++;
                }

	 if( index > 0) {
			argcp++;
                        strncpy(argvp[argcp-1],command+start_index,index-start_index);
         }
	
	printf("\n");	
	for(i = 0 ; i < argcp; i++) 
		printf("%s        ",argvp[i]);
	printf("\n");
#endif
}



int main(int argc, char** argv) {
			
	// Read the argument1 to get the file name
	//exec.sh file here.

	int fd;
	//fd = open("temp/exec.sh");
	fd = open(argv[1]);
	if(fd == -1) {
		printf("Unable to open file %s. Enter complete path\n",argv[1]);	
		return -1;
	}
	char read_buf[1024];


	//shared_page[0] = number of lines

	int bytes_read = 0;	
	char command_buf[128];
	//int num_lines = 0;
	//printf("PATH is %s\n",PATH);

	while((bytes_read = read(fd,read_buf,1023)) != 0) {
		read_buf[bytes_read] = '\0';
		//printf("%s\n",read_buf);
		
		
		// Check if a new line is in the read_buf
		int index = 0, start_index = 0;
		
		while(read_buf[index] != '\0') {
			if(read_buf[index] == '\n') {
				if((index - start_index) > 0) {
					strncpy(command_buf,read_buf+start_index,index-start_index);
					if((command_buf[0] != '\n')) {
						// Execute command buf here
						//strcpy(shared_page,command_buf);	
						//shared_page += 50;
						printf("command_buf is %s",command_buf);
						//execute(command_buf);
						//Fork
						// Exec in the child
						// Wait in the parent
					}
                                        start_index = index + 1;
				}
			}
			index++;
		}
	}

return 0;
}


