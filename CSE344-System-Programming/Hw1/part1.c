#include "part1.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int appendBytes(int fd, size_t count, bool append_flag){
    
    int totalbytes = 0;
    //struct flock lock;
    int byteswritten = 0;
    char byte = 'x';
    /*memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    fcntl(fd, F_SETLKW, &lock);*/

    while (totalbytes < count) {
        
        if (append_flag) {
            while ((byteswritten = write(fd, &byte, 1)) == -1 && errno == EINTR);
        } 
        else{
            do{
                lseek(fd, 0, SEEK_END);
            }while((byteswritten = write(fd, &byte, 1)) == -1 && errno == EINTR);
            
        }
        if (byteswritten == -1) {
            perror("Failed to write to file");
            totalbytes = -1;
            break;
        }
        totalbytes += byteswritten;
    }
    /*lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    */
    return totalbytes;

}





