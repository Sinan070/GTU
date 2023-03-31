#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<string.h>
#include "my_utils.h"



int write_to_file(int fd, const void *buf, int count){
int totalbytes = 0;
char *ptr = (char*) buf;
int byteswritten = 0;

int len = strlen(ptr);
int retval =0;
while(totalbytes < len){

        while(((byteswritten = write(fd, ptr, count)) == -1) && errno == EINTR){};
            if(byteswritten == -1){
                perror("Failed to write to file");
                retval = -1;
                break;
            }
        totalbytes += byteswritten;
        ptr += byteswritten;
    }
return retval;
}