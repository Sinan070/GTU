#define _POSIX_C_SOURCE  200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "com.h"
#include <ctype.h>
#include "my_utils.h"
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>



static char client_req_Fifo[CLIENT_FIFO_NAME_LEN];
static char client_res_Fifo[CLIENT_FIFO_NAME_LEN];
static char client_res_Fifo_wr[CLIENT_FIFO_NAME_LEN];

int cleanUp(int client_req_fd, int client_res_fd, int client_res_fd_wr, \
                            char* client_res_fifo, char* client_res_fifo_wr){
    close(client_req_fd);
    close(client_res_fd);
    close(client_res_fd_wr);

    // unlink any associated files
    unlink(client_res_fifo);
    unlink(client_res_fifo_wr);
    unlink(client_req_Fifo);

}



int handleUpload(Request request, Response response, const int client_res_fd_wr){
    char* words[2];
    int i;
    int word_count;
    int retval = 0;
    int fd;
    for(i = 0 ; i < 2; ++i ){
        words[i] = (char *) malloc(sizeof(char)* 256);
    }
    // split request into desired format
    word_count = split_string_into(request.msg, words,3);
    if( word_count == -1){
        retval = -1;
        for(i = 0 ; i < 2; ++i ){
            free(words[i]);
        }   
    }
    else{
        // check file is exist in client or not
        if(access(words[1], F_OK) == -1){
            memset(&response,'\0', sizeof(Response));
            strncpy(response.package, "Error Code", 33);
            write_to_file(client_res_fd_wr, sizeof(Response), &response);  
            retval = -1;
            perror("Error : ");
        }
        else{
            // open file as read
            fd = open(words[1], O_RDONLY);
            if(fd == -1){
                retval = -1;
            }
            else{
                // get file permission and send to the server
                mode_t file_per = getFilePermission(words[1]);
            
                char file_permission[4];
                snprintf(file_permission, 4, "%u",file_per);
                
                strncpy(response.package,file_permission,4);
                sendFilePermission(&response, sizeof(Response), client_res_fd_wr);
                // read file into the CLIENT_RESPONSE_FIFO_WR For server
                if(read_file_into(fd, &response, sizeof(Response), client_res_fd_wr) == -1){
                    retval = -1;
                }
                }
                close(fd);
        }
        
    }
}




int main(int argc, char * argv[]){
    
    int client_req_fd;
    int client_res_fd;
    int client_res_fd_wr;
    int server_log_fd;
    pid_t pid = getpid();
    
    Request request;
    Response response;
    int num_read;

    int server_fd ;
    int fd;
    sem_t * sem;
    sigset_t set;

    umask(0);
    
    
    if(argc != 2 && argv)
    
    
    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);

    

    snprintf(client_res_Fifo, CLIENT_FIFO_NAME_LEN, CLIENT_RESPONSE_FIFO_TEMPLATE, (long) getpid());
    fprintf(stderr,"%s",client_res_Fifo);
    if(mkfifo(client_res_Fifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        fprintf(stderr,"Error creating fifo %s\n",client_res_Fifo);
        exit(EXIT_FAILURE);
    }

    snprintf(client_res_Fifo_wr,CLIENT_FIFO_NAME_LEN, CLIENT_RESPONSE_FIFO_TEMPLATE_WR, (long) getpid());
    if(mkfifo(client_res_Fifo_wr, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        fprintf(stderr,"Error creating fifo %s\n",client_res_Fifo_wr);
        exit(EXIT_FAILURE);
    }

    snprintf(client_req_Fifo,CLIENT_FIFO_NAME_LEN, CLIENT_REQUEST_FIFO_TEMPLATE, (long) getpid());
    if(mkfifo(client_req_Fifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        fprintf(stderr,"Error creating fifo %s\n",client_req_Fifo);
        exit(EXIT_FAILURE);
    }


    server_fd = open(SERVER_FIFO,O_WRONLY);
    if(server_fd == -1){
        exit(EXIT_FAILURE);
    }
    
    request.pid = pid;
    memset(request.msg,'\0',256);
    strcpy(request.msg , argv[1]);

    if(write(server_fd, &request, sizeof(Request)) != sizeof(Request)){
        fprintf(stderr,"Error writing to fifo %s\n",SERVER_FIFO);
        exit(EXIT_FAILURE);
    }
    
    close(server_fd);

    
    
    
    fprintf(stdout, "%s", ">> Waiting for QUE...");
    fflush(stdout);
   
    
    snprintf(client_req_Fifo, CLIENT_FIFO_NAME_LEN, CLIENT_REQUEST_FIFO_TEMPLATE, (long) getpid());
    client_req_fd = open(client_req_Fifo, O_WRONLY);
    if(client_req_fd == -1){
        perror("Error 1:");
        fprintf(stderr,"%s","hata");
        exit(EXIT_FAILURE);
    }

    //printf(stderr,"%s","gecti1");

    
    client_res_fd = open(client_res_Fifo, O_RDONLY) ;
    if(client_res_fd == -1){
        perror("Error2 :");
        fprintf(stderr,"%s","hata");
        exit(EXIT_FAILURE);
    }

    client_res_fd_wr = open(client_res_Fifo_wr, O_WRONLY);
    if(client_res_fd_wr == -1){
        perror("Error3 :");
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
        int len = strlen(request.msg);
        request.msg[len-1] = '\0';


        if(write(client_req_fd, &request, sizeof(Request)) != sizeof(Request)){
            exit(EXIT_FAILURE);
        }
        memset(&response.package,'\0',sizeof(Response));

        if((strncmp(request.msg, "help", 4) == 0)){
            //fprintf(stderr,"%s","gecti5");
            if(read_file_into(client_res_fd, &response, sizeof(Response), STDOUT_FILENO) == -1){
                
            }
        }
        else if(strncmp(request.msg, "readF",5) == 0){
           

            /* finding downloadable files*/
            int word_count = get_word_count(request.msg);

            if(word_count == 2){
                
                if(read_file(client_res_fd, &response, sizeof(Response)) == -1){
                    fprintf(stdout, "%s",response.package);
                }
                else if(strcmp(response.package, "Error Code") == 0){
                    fprintf(stdout,"%s","There is no such a file in server\n");
                }
                else{
                    if(fd != -1){
                        if(read_file_into(client_res_fd, &response, sizeof(Response), STDOUT_FILENO) == -1){
                            perror("Error : ");
                        }
                    }
                    else{
                        perror("Error : ");
                    }
                }
                
            }
            
            
            
        }


        else if(strncmp(request.msg, "writeT",6) == 0){
            read_file(client_res_fd, &response, sizeof(Response));
            
        }
        
        else if(strncmp(request.msg, "download", 8) == 0){

            /* finding downloadable files*/
            char *words[2];
            int i;
            for (i = 0; i < 2; i++)
            {
                words[i] = (char*)malloc((sizeof(char)*256));
            }
            // SPLIT REQUEST
            int word_count = split_string_into(request.msg, words,2);

            if(word_count == -1){
                for (i = 0; i < 2; i++)
                {
                    free(words[i]);
                }   
            }
            // Check file format

            if(word_count != -1){
                
                char  file_name[256];
                snprintf(file_name, 256, "download/%s",words[1]);    
            
                // READ CLIENT_RESPONSE_FIFO TO FIND FILE EXIST OR NOT
                if(read_file(client_res_fd, &response, sizeof(Response)) == -1){
                    fprintf(stdout, "%s",response.package);
                }
                else if(strcmp(response.package, "Error Code") == 0){
                    fprintf(stdout,"%s","There is no such a file in server\n");
                }
                // GET FILE PERMISSON FROM CLIENT_RESOONSE_FIFO
                else{
                    
                    mode_t file_per = (unsigned int)atoi(response.package);
                    // CREATE FILE IF NOT EXIST AND READ FIFO INTO THIS FILE
                    fd = open(file_name, O_CREAT|O_WRONLY,file_per);
                    if(fd != -1){
                        if(read_file_into(client_res_fd, &response, sizeof(Response), fd) == -1){
                            perror("Error : ");
                        }

                        close(fd);
                    }
                    else{
                        perror("Error : ");
                    }
                }
                
            }
            

        }
        else if(strncmp(request.msg, "upload", 6) == 0){
            
            if(handleUpload(request, response, client_res_fd_wr) == -1){
                fprintf(stderr, "%s", "Error Occurs");

            }
        }
        else if(strcmp(request.msg, "list") == 0){
            if(read_file_into(client_res_fd, &response, sizeof(response), STDOUT_FILENO) == -1){
                fprintf(stderr,"%s","Error occurs\n");
            };
        }
        else if(strcmp(request.msg , "quit") == 0){
            cleanUp(client_req_fd, client_res_fd, client_res_fd_wr, client_res_Fifo, client_res_Fifo_wr);
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(request.msg, "killServer") == 0){

        } 
        else{

        }
    
        
        
        
        

        
    }
    
    exit(0);
}