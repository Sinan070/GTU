#define _POSIX_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include "signalsHandler.h"
#include <time.h>
#include <errno.h>

#define WRITE_PERMS 0777 // read-write-execute for everything
#define WRITE_FLAGS (O_RDONLY | O_WRONLY  | O_CREAT) // write flags
#define sigAct(s, sact, restrict) if(sigaction(s, sact, restrict) != 0) { perror("SIGACTION ERROR");}

extern errno;

int getcmd(char *buf, int nbuf);
int  runcmd(char **cmds, int n_cmds ,int fd);
int parsecmd(char *cmd, char **ptr);

int logFile(char* buf,int fd);
void lock_file(int fd, int lock_type);
void unlock_file(int fd);


void getCurrentTime(char *timestamp);


int main() {
    char *cmds[20] = {0}; 
    static char buf[100];
    int fd;
    int fd2 ;
    int cmdNum =0;
    int pid;
    int status;
    char timeStamp[20];
    char currentDir[1024];
    
    
    /* Sigaction part for Desired Signal*/
    sigset_t sigset;
    struct sigaction sact;
    
    sigemptyset(&sact.sa_mask);
    sact.sa_flags = 0;
    sact.sa_handler = signalHandler;
    //if(sigaction(SIGKILL, &sact, NULL) != 0) { perror("SIGACTION ERROR"); exit(1);};
    if(sigaction(SIGINT, &sact, NULL) != 0) { perror("SIGACTION ERROR SIGINT"); exit(1);};
    if(sigaction(SIGTSTP, &sact, NULL) != 0) { perror("SIGACTION ERROR SIGTSTP"); exit(1);};
    
    

    getCurrentTime(timeStamp); // get current time year-month-day-hour-minute-second
    
    // Open file for logging
    if ((fd2 = open(timeStamp, WRITE_FLAGS, WRITE_PERMS)) == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }


    
    // allocate memory for commands
    for (int i = 0; i < 20; ++i) {
        cmds[i] = (char *) malloc(sizeof(char) * 100);
        memset(cmds[i], 0, sizeof(char) * 100); // initialize memory to zero
    }

    // Ensure that three file descriptors are open.
    while ((fd = open("console", O_RDWR)) >= 0) {
        if (fd >= 3) {
            close(fd);
            break;
        }
    }
    
    
    // Read and run input commands.
    while (1) {
        if(getcmd(buf, sizeof(buf)) >= 0){
            if(buf[0] == ':' && buf[1] == 'q' && buf[2] == '\n'){
                for(int i = 0; i < 20; ++i) {
                    free(cmds[i]); 
                }
                close(fd);
                exit(EXIT_SUCCESS);
            }
            if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') {
                // Chdir must be called by the parent, not the child.
                buf[strlen(buf) - 1] = 0; // chop \n
                if (chdir(buf + 3) < 0)
                    printf("cannot cd %s\n", buf + 3);
                continue;
            }
            cmdNum = parsecmd(buf,cmds);
            if(cmdNum > 20){
                perror("Maximum Command Number is Exeeded\n");
            }
           
            runcmd(cmds,cmdNum, fd2);
           
           
        }
        

    }
    
    //exit(0);
}


int getcmd(char *buf, int nbuf)
{
    int retval = 0;
    char currentDir[1024];
    getcwd(currentDir,1024);
    printf("%s $ ",currentDir);
    memset(buf, 0, nbuf);
    fgets(buf, nbuf,stdin);
    if(buf[0] == 0) // EOF
        retval = -1;
    return retval;
}

int parsecmd(char *cmd, char **ptr) {
    int i = 0;
    
    char *token = strtok(cmd, "|");
    while (token != NULL) {
        strcpy(ptr[i], token);
        ++i;
        token = strtok(NULL, "|");
    }
    if(i != 0){
        int len = strlen(ptr[i-1]);
        
        ptr[i-1][len-1] = '\0';
    }
    return i;
}

int  runcmd(char **cmds, int n_cmds ,int fd) {
    int i, j;
    int *pfd = calloc(2 * n_cmds, sizeof(int)); // allocate memory for pipes
    int status;
    int pid;
    int childpid;
    // create all pipes
    for (i = 0; i < n_cmds - 1; i++) {
        if (pipe(pfd + i * 2) == -1) {
            perror("pipe");
            exit(1);
        }
    }
    
    // execute all commands in separate processes
    for (i = 0; i < n_cmds; i++) {
        switch (fork()) {
            case -1:
                perror("fork");
                exit(1);
            case 0:
                lock_file(fd, F_WRLCK);
                // set up input redirection
                if (i != 0) {
                    if(close(pfd[((i-1)*2) +1]) == -1){
                        perror("close");
                        exit(1);
                    }
                    if(pfd[(i - 1) * 2] != STDIN_FILENO){

                        if (dup2(pfd[(i - 1) * 2], STDIN_FILENO) == -1) {
                            perror("dup2");
                            exit(1);
                        }
                        if(close(pfd[(i - 1) * 2]) == -1 ){
                            perror("close");
                            exit(1);
                        }
                    }
                }
                // set up output redirection
                if (i != n_cmds - 1) {

                     if(close(pfd[i*2]) == -1){
                        perror("close");
                        exit(1);
                    }
                    if(pfd[(i * 2) +1] != STDOUT_FILENO){

                        if (dup2(pfd[(i * 2)  +1], STDOUT_FILENO) == -1) {
                            perror("dup2");
                            exit(1);
                        }
                        if(close(pfd[(i *2) + 1]) == -1 ){
                            perror("close");
                            exit(1);
                        }
                    }
                }

                int pid = getpid();
                //fprintf(fd, "Command : %s   Parent id : %d\n", cmds[i],pid);
                // execute command
                char buf[100];
                sprintf(buf,"Process id : %d ->> Command : %s\n",pid,cmds[i]);
                logFile(buf, fd); 
                unlock_file(fd);
                execl("/bin/sh", "sh", "-c", cmds[i], NULL);
                perror("execl");
                exit(1);
            default:
                break;
        }
    }

    // close all pipes in parent process
    for (i = 0; i < 2 * n_cmds; i++) {
        if (pfd[i] != 0) {
            if (close(pfd[i]) == -1) {
                perror("close");
                exit(1);
            }
        }
    }

    // wait for all child processes to terminate
    for (i = 0; i < n_cmds; i++) {
        childpid = waitpid(-1,&status,0);
        if ( childpid == -1) {
            perror("wait");
            fprintf(stderr,"%d",status);
            exit(1);
        }
        if (WIFEXITED(status)) {
            printf("Child processssss %d terminated normally with exit status %d\n",childpid, WEXITSTATUS(status));
        }else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by a signal with signal number %d\n",childpid, WTERMSIG(status));
        }
    }

    free(pfd); // free memory allocated for pipes
    return 0;
}




void lock_file(int fd, int lock_type) {
    struct flock fl;
    fl.l_type = lock_type;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }
}

void unlock_file(int fd) {
    struct flock fl;
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }
}




int logFile(char* buf, int fd){
    int totalbytes = 0;
    char *ptr = (char*) buf;
    int byteswritten = 0;

    int len = strlen(ptr);
    int retval =0;
    while(totalbytes < len){
        while(((byteswritten = write(fd, ptr, len)) == -1) && errno == EINTR){};
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

void getCurrentTime(char *timestamp){
    
    time_t current_time;
    struct tm *time_info;
    current_time = time(NULL);
    time_info = localtime(&current_time);
    strftime(timestamp, 20, "%Y-%m-%d-%H-%M-%S", time_info);
    
}




