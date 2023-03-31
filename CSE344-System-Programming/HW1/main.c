#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "part1.h"
#include "part2.h"
#include "my_utils.h"

#define WRITE_PERMS 0777 // read-write-execute for everything


int part3(){
    int oldfd, newfd1, newfd2, badfd; //file descriptors
    char *test = "This is a test text "; // sample test text
    int len = strlen(test);
    badfd = 1023; // represent bad file descriptor

    // open the test.txt , use read-write , create and append flag.
    if ((oldfd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, WRITE_PERMS)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    // open the test.txt , use read-write , create and append flag.
    if ((newfd2 = open("test1.txt", O_RDWR | O_CREAT | O_APPEND, WRITE_PERMS)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    // calling dup2 function with bad file descriptor
    if(my_dup2(oldfd, badfd) == -1 && errno == EBADF){
        perror("ERROR IS SHOWN THERE. Newfd is not valid\n");   
    }

    // calling dup2 function with bad file descriptor
    if(my_dup2(badfd,oldfd) == -1 && errno == EBADF){
        perror("ERROR IS SHOWN THERE. Oldfd is not valid\n");
    }

    printf("\n\n");
    //write to file
    write_to_file(oldfd, test, len);
    
    printf("TEXT IS WRITED TO THE FILE BEFORE MY_DUP(). OFFSET IS : %ld\n" , lseek(oldfd, 0 , SEEK_CUR));
    // calling dup function and write
    newfd1 = my_dup(oldfd);
    write_to_file(newfd1, test, len);
    printf("TEXT IS WRITED TO THE FILE AFTER MY_DUP(). OFFSET IS : %ld\n" , lseek(oldfd, 0 , SEEK_CUR));
    

    // calling dup2 function and write
    my_dup2(oldfd, newfd2);
    write_to_file(newfd2, test, len);
    printf("TEXT IS WRITED TO THE FILE AFTER MY_DUP2(). OFFSET IS : %ld\n" , lseek(oldfd, 0 , SEEK_CUR));
    
    // close files
    if (close(oldfd) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
        
    }
    if (close(newfd1) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
        
    }
    if (close(newfd2) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }
    return 0;    

}

int part1(const int argc, char *argv[]){
    int fd;
    int write_flags;
    int count;    
    bool append_flag = true;
    int totalbytes;

    write_flags = O_RDONLY | O_WRONLY  | O_CREAT; // write flags

    // check command line arguments 
    if(argc <3 || argc >4){
        fprintf(stderr, "Usage: %s filename num-bytes [x]\n", argv[0]);
        return -1;
    }
    
    count = atoi(argv[2]);    // get count number 
    
    // check x flag
    if (argc == 4 && strcmp(argv[3], "x") == 0) {
        append_flag = false;
    }
    else{
        write_flags |= O_APPEND;
    }
    
    
    // open file
    if ((fd = open(argv[1], write_flags, WRITE_PERMS)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    if (append_flag) {
        printf("Appending %d bytes to %s\n", count, argv[1]);
    } else {
        printf("Writing %d bytes to %s\n", count, argv[1]);
    }
    
    // appendbytes
    totalbytes = appendBytes(fd, count, append_flag);
 
    printf("Wrote %d bytes to %s\n", totalbytes, argv[1]);

    //close file
    if (close(fd) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }
    return 0;


} 

// main
int main(int argc, char *argv[]) {
    printf("*****PART1****** \n");
    part1(argc, argv);
    printf("\n\n");
    printf("******PART3******\n\nDUP functions implemented in part2 is used for PART3\n\n");
    part3();

    return 0;
}