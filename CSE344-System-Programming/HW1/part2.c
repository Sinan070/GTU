#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern errno;

int my_dup(int oldfd){
    int retval;
    if(fcntl(oldfd,F_GETFD) < 0)
    {
        errno = EBADF; 
        retval = -1;
    }
    else{
        retval = fcntl(oldfd, F_DUPFD, 0);
    }
    return retval;
}

int my_dup2(int oldfd, int newfd){
    int retval;
    
    //printf("%d", fcntl(oldfd, F_GETFD));
    
    if(fcntl(oldfd, F_GETFD) < 0){
        retval = -1;
        errno = EBADF;
        
    }
    else if(oldfd == newfd){
        
        retval =  newfd;
    }
    else{
        
        if(fcntl(newfd, F_GETFD) >= 0){
            if(close(newfd) == -1){
                fprintf(stderr, "Failed to close file\n");
                exit(EXIT_FAILURE);
            }
            
            retval = fcntl(oldfd, F_DUPFD, newfd);
        }
        else {
            
            retval = -1;
            errno = EBADF;
        }
    }
    return retval;
}