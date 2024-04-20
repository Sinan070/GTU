#ifndef __SIGNAL_HANDLER_C
#define __SIGNAL_HANDLER_C
#include <sys/wait.h>
#include <stdio.h>
void handle_sigchld(int sig) {
    // Catch and handle the termination of the child process
    //fprintf(stderr,"%s","Child process terminated.\n");
    waitpid(-1,NULL,0); //olmaması lazım
}

int handle_client_sigterm(int sig){
    
}
#endif