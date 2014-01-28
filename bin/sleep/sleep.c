#include <stdio.h>


uint64_t atoi(volatile char* num_string, int base) {

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


int main(int argc,char* argv[]) {
	//printf("\nsleeptime is %d\n",atoi(argv[1],10));
	sleep(atoi(argv[1],10));
return 0;

}
