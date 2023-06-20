#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "com.h"
#include <errno.h>

static char client_req_Fifo[CLIENT_FIFO_NAME_LEN];
static char client_res_Fifo[CLIENT_FIFO_NAME_LEN];

int main(int argc, char * argv[]){
    
    int client_req_fd;
    int client_res_fd;
    
    pid_t pid = getpid();
    
    Request request;
    Response response;
    int num_read;

    int server_fd ;
    
    
    snprintf(client_res_Fifo, CLIENT_FIFO_NAME_LEN, CLIENT_RESPONSE_FIFO_TEMPLATE, (long) getpid());
    fprintf(stderr,"%s",client_res_Fifo);
    if(mkfifo(client_res_Fifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        fprintf(stderr,"Error creating fifo %s\n",client_req_Fifo);
    }

    

    request.pid = pid;
    memset(request.msg,'\0',256);
    strcpy(request.msg , argv[1]);
    
    server_fd = open(SERVER_FIFO,O_WRONLY);
    if(server_fd == -1){
        exit(EXIT_FAILURE);
    }
    if(write(server_fd, &request, sizeof(Request)) != sizeof(Request)){
        fprintf(stderr,"Error writing to fifo %s\n",SERVER_FIFO);
        exit(EXIT_FAILURE);
    }
    

    
    
    fprintf(stdout, "%s", ">> Waiting for QUE...");
    fflush(stdout);
   
    snprintf(client_req_Fifo, CLIENT_FIFO_NAME_LEN, CLIENT_REQUEST_FIFO_TEMPLATE, (long) getpid());
    client_req_fd = open(client_req_Fifo, O_WRONLY);
    if(client_req_fd == -1){
        fprintf(stderr,"%s","hata");
        exit(EXIT_FAILURE);
    }

    //fprintf(stderr,"%s","gecti1");

    
    client_res_fd = open(client_res_Fifo, O_RDONLY);
    if(client_res_fd == -1){
        fprintf(stderr,"%s","hata");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "%s", " Connection established :\n");
    fflush(stdout);

    
    
    while (1)
    {   
        //fprintf(stderr,"%s","gecti1");
        fprintf(stdout, "%s", ">> Enter comment : ");
        
        memset(request.msg, '\0', 256);
        fgets(request.msg, 256, stdin);
        
        if(write(client_req_fd, &request, sizeof(Request)) != sizeof(Request)){
            exit(EXIT_FAILURE);
        }
        memset(&response.package,'\0',sizeof(Response));
        if(read(client_res_fd,&response,sizeof(Response)) > 0){
            fprintf(stdout,"%s", response.package);   
            fflush(stdout); 
            //fprintf(stderr,"%s","gecti");
            if(num_read == 0){
                continue;
            }
        }
        
    }
    
    exit(0);
}