#define _POSIX_C_SOURCE  200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "circular_queue.h"
#include "com.h"
#include <ctype.h>
#include "my_utils.h"
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/file.h>


void handle_sigchld(int sig);


int handle_writeT(Request request, Response response, int client_res_fd , int client_res_fd_wr){
    char *words[4];
    int i ;
    int retval = 0;
    int fd;
    int word_count = 0;
    int is_Number;
    
    
    for(i = 0 ; i < 4; ++i ){
        words[i] = (char *) malloc(sizeof(char)* 256);
    }

    word_count = split_string_into(request.msg, words,4);
    if( word_count == -1){
        retval = -1;
        for(i = 0 ; i < 4; ++i ){
            free(words[i]);
        }   
    }
    
    if(word_count == 4){
        is_Number = isNumber(words[2]);
    }
    if ((word_count == 3 || (word_count == 4 && is_Number))) {
        retval = 0;
    }
    else retval = -1;
    
    
    if(retval != -1){
        if(access(words[1], F_OK) == -1){
            memset(&response,'\0', sizeof(Response));
            snprintf(response.package, sizeof(Response),"%s", "Error Code");
            write_to_file(client_res_fd, sizeof(Response), &response);  
        }
        else{
            snprintf(response.package, sizeof(Response),"File < %s > is found in server\n", words[1]);
            write_to_file(client_res_fd, sizeof(Response), &response);  
            fd = open(words[1], O_WRONLY| O_APPEND);
            if(fd == -1){
                retval = -1;
            }
            else{
                if (flock(fd, LOCK_SH) == -1) {
                    perror("Error locking file for reading");
                    retval = -1;
                }
                if(word_count == 3){
                    if(read_file_into(client_res_fd_wr, &response, sizeof(Response), fd) == -1){
                        retval = -1;
                    }
                }
                else if(word_count == 4){
                    //fprintf(stderr,"%s","gecti7");
                    int line_num = atoi(words[2]);
                    if(read_line_of_file_into(client_res_fd_wr, &response, sizeof(Response), line_num, fd)){
                        retval = -1;
                    }
                }
                if (flock(fd, LOCK_UN) == -1) {
                    perror("Error unlocking file");
                    retval = -1;
                }
            }
            close(fd);
        }
    }
        
    //close(client_res_fd);
    return retval;



}


int handleHelp(const Request request, Response response, const int client_res_fd){
    int retval = 0;
            if(strcmp(request.msg , "help" ) == 0){
                
                strncpy(response.package, "\tAvaliable Comments are:\nhelp, list, readF, writeT, upload, download, quit, killServer\n",sizeof(Response));
            
            }
            
            else if(strcmp(request.msg, "help readF") == 0){
                strncpy(response.package, "readF <file> <line #>\n\trequests to display the # line of the <file>,"\
                "if no line number is given\n\t"\
                "the whole contents of the file is requested (and displayed on the client side)\n",sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help writeF") == 0){
                strncpy(response.package, "writeT <file> <line #> <string>\n\t"\
                "request to write the content of “string” to the #th line the <file>, if the line # is not given\n\t"\
                "writes to the end of file. If the file does not exists in Servers directory creates and edits the\n\t"\
                "file at the same time"
                ,sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help list") == 0){
                strncpy(response.package, "-list\n\tSends a request to display the list of files in Servers directory\n",sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help upload") == 0){
                strncpy(response.package, "upload <file>\n\t"\
                "uploads the file from the current working directory of client to the Servers directory\n\t"\
                "(beware of the cases no file in clients current working directory and file with the same\n\t"
                "name on Servers side)\n"
                ,sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help dowload") == 0){
                strncpy(response.package,"download <file>\n\trequest to receive <file> from Servers directory to client side\n",sizeof(Response));
            }
            else if(strcmp(request.msg, "help quit") == 0){
                strncpy(response.package,"quit\n\tSend write request to Server side log file and quits\n",sizeof(Response));
    
            }
            else if(strcmp(request.msg, "help killserver") == 0){
                strncpy(response.package,"killServer\n\tSends a kill request to the Server\n",sizeof(Response));

            }
            else {
                strncpy(response.package,"There is no such a command found\n",sizeof(Response));
                retval = -1;
            }
            if(write_to_file(client_res_fd, sizeof(response), &response ) == -1){
                retval = -1;
                
            }

    return retval;

}
int handle_readF(Request request, Response response, const int client_res_fd){
     char* words[2];
    int i;
    int word_count;
    int retval = 0;
    int fd;
    char file_name[256];
    // SPLITTING REQUEST
    for(i = 0 ; i < 2; ++i ){
        words[i] = (char *) malloc(sizeof(char)* 256);
    }
    word_count = split_string_into(request.msg, words,2);
    if( word_count == -1){
        retval = -1;
        for(i = 0 ; i < 2; ++i ){
            free(words[i]);
        }   
    }
    else{
        // CHECK IS FILE EXIST
        snprintf(file_name,256,"server_files/%s",words[1]);
        if(access(file_name, F_OK) == -1){
            memset(&response,'\0', sizeof(Response));
            strncpy(response.package, "Error Code", 33);
            write_to_file(client_res_fd, sizeof(Response), &response);  
            retval = -1;
        }
        else{
            //OPEN DESIRED FILE
            fd = open(file_name, O_RDONLY);
            if(fd == -1){
                memset(&response,'\0', sizeof(Response));
                strncpy(response.package, "Error Code", 33);
                retval = -1;
            }
            else{  
                // LOCK FILE TO ENSURE SYNC
                if(flock(fd , LOCK_SH) == -1){
                    memset(&response,'\0', sizeof(Response));
                    strncpy(response.package, "Error Code", 33);
                    retval = -1;
                }
                else{
                    memset(&response,'\0', sizeof(Response));
                    strncpy(response.package, "Found", 33);  
                }
                // WRITE TO THE CLIENT_RESPONSE_FIFO
                write_to_file(client_res_fd, sizeof(Response), &response);
                if((retval != -1) && read_file_into(fd, &response, sizeof(Response), client_res_fd) == -1){
                    retval = -1;
                }
                // UNLOCK FILE
                if(flock(fd, LOCK_UN) == -1){
                     perror("Error unlocking file");
                     retval = -1;
                }
            }   //CLOSE FILE
                close(fd);
        }
        
    }

    
    return retval;

}


int handle_Dowload(Request request, Response response, const int client_res_fd ){
    char* words[2];
    int i;
    int word_count;
    int retval = 0;
    int fd;
    char file_name[256];
    int bytesSend = 0;
    for(i = 0 ; i < 2; ++i ){
        words[i] = (char *) malloc(sizeof(char)* 256);
    }
    // SPLIT REQUEST 
    word_count = split_string_into(request.msg, words,2);
    if( word_count == -1){
        retval = -1;
        for(i = 0 ; i < 2; ++i ){
            free(words[i]);
        }   
    }
    else{
        // CHECK EXISTING OF FILE
        snprintf(file_name,256,"server_files/%s",words[1]);
        if(access(file_name, F_OK) == -1){
            memset(&response,'\0', sizeof(Response));
            strncpy(response.package, "Error Code", 33);
            write_to_file(client_res_fd, sizeof(Response), &response);  
            retval = -1;
        }
        else{
            //OPEN FILE
            fd = open(file_name, O_RDONLY);
            if(fd == -1){
                retval = -1;
            }
            else{
                // SEND FILE PERMISSION
                mode_t file_per = getFilePermission(file_name);
            
                char file_permission[4];
                snprintf(file_permission, 4, "%u",file_per);
                
                strncpy(response.package,file_permission,4);
                sendFilePermission(&response, sizeof(Response), client_res_fd); 
                //LOCK FILE
                if(flock(fd , LOCK_SH) == -1){
                    memset(&response,'\0', sizeof(Response));
                    strncpy(response.package, "Error Code", 33);
                    retval = -1;
                }

                // SEND FILE 
                bytesSend = read_file_into(fd, &response, sizeof(Response), client_res_fd);
                
                if((retval != -1) && bytesSend == -1){
                    retval = -1;
                }
                else{
                    retval = bytesSend;                    
                }
                //UNLOCK FILE
                if (flock(fd, LOCK_UN) == -1) {
                    perror("Error unlocking file");
                    retval = -1;
                }
                
                }
                
                close(fd);
        }
        
    }
    
    
    return retval;

}


int handle_Upload(Request request, Response response, const int client_res_fd_wr){
    /* finding downloadable files*/

        char *words[2];
        int i;
        int fd;
        int retval = 0;
        for (i = 0; i < 2; i++)
        {
            words[i] = (char*)malloc((sizeof(char)*256));
        }
        // get word count and split request into desired format
        int word_count = split_string_into(request.msg, words,2);
        // Check file format
        //first we need to find file permission

        if(word_count != -1){
            
            char  file_name[256];
            snprintf(file_name, 256, "server_files/%s",words[1]);    
            // read CLEINT_RESPONSE_FIFO_WR TO CHECK FILE EXIST OR NOT
            if(read_file(client_res_fd_wr, &response, sizeof(Response))== -1){
                retval = -1;
                perror("Error : ");
            }
            else if(strncmp(response.package, "Error Code", sizeof(Response)) == 0  ){
                retval = -1;
            }
            else{
                // GET FILE PERMISSON AND CREATE OR OPEN FILE IN SERVER
                mode_t file_per = (unsigned int)atoi(response.package);

                fd = open(file_name, O_CREAT|O_WRONLY,file_per);

                if(fd != -1){
                    // LOCK THE FILE
                      if(flock(fd , LOCK_SH) == -1){
                        memset(&response,'\0', sizeof(Response));
                        strncpy(response.package, "Error Code", 33);
                        retval = -1;
                        }
                    // READ FIFO INTO THE UPLOADED FILE
                    if(read_file_into(client_res_fd_wr, &response, sizeof(Response), fd) == -1){
                        perror("Error : ");
                        retval = -1;
                        
                    }
                    // UNLOCK FILE
                     if (flock(fd, LOCK_UN) == -1) {
                       perror("Error unlocking file");
                        retval = -1;
                    }

                    close(fd);
                }
                else{
                    perror("Error : ");
                    retval = -1;

                }
            }
        }
        return retval;
            
}


int handle_list(int fd){
    int retval = 0;
    pid_t pid = fork();
    if(pid < 0){
        perror("Error : ");
        retval = -1;
    }
    if(pid == 0){
        dup2(fd, STDOUT_FILENO);
        execl("/bin/ls", "ls","-l","server_files" ,NULL);
        perror("execl");
        retval = -1;
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            //printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            perror("Error : ");
            retval = -1;
        }
    }
    close(fd);
    return retval;

}


int main(int argc, char *argv[]){

    char sv_log_path[100];
    char client_req_fifo[256];
    char client_res_fifo[256];
    char client_res_fifo_wr[256];
    char *dir_name = argv[1];
    int max_clients = atoi(argv[2]);
    int server_fd;
    int dummy_fd1;
    int dummy_fd2;
    int *client_num_shm;
    int client_req_fd;
    int client_res_fd;
    int client_res_fd_wr;
    
    int c_pid;

    int *sigKill_shm;

    long int curr_req_pid;
    Request request;
    Response response;
    sigset_t set;
    int num_read;
    int num_write;
    Queue * waiting_QUE;
    int waiting_Que_shmid;
    

    int current_clients[max_clients];
    int client_log_fd;
    

    if(argc != 3 || (argc == 3 && max_clients == 0) ){
        fprintf(stderr,"Invalid Usage\n");
    }


    //Request request_queue[max_clients];

    __pid_t pid = getpid();

    umask(0);

    const char* client_num_shm_name = "/client_num_shm";
    sem_t* client_num_sem = sem_open("/client_num_sem", O_CREAT,0644, 1);

    const char* sigKill_shm_name = "/sigKill_shm_shm";


    waiting_Que_shmid = shm_open("/queue_shm", O_CREAT | O_RDWR, 0644);
    if(waiting_Que_shmid == -1){
        perror("shm_open : ");
        exit(EXIT_FAILURE);
    }
    ftruncate(waiting_Que_shmid, sizeof(Queue));
    waiting_QUE = (Queue*) mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, MAP_SHARED, waiting_Que_shmid, 0);
    if (waiting_QUE == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    waiting_QUE->rear = 99;
    waiting_QUE->front = 99;
    waiting_QUE->size = 100;

    waiting_QUE->array = (long int *) mmap(NULL, sizeof(int) * 100, PROT_READ | PROT_WRITE, MAP_SHARED, waiting_Que_shmid, 0);



    
    if(client_num_sem == SEM_FAILED){
        perror("sem_open failed : ");
        exit(EXIT_FAILURE);
    }

    int client_num_shm_fd = shm_open(client_num_shm_name, O_CREAT | O_RDWR, 0644);
    int sigKill_shm_fd = shm_open(sigKill_shm_name,  O_CREAT | O_RDWR, 0644);

    if(client_num_shm_fd == -1){
        perror("shm_open failed : ");
        exit(EXIT_FAILURE);
    }
    if(sigKill_shm_fd == -1){
        perror("shm_open failed : ");
        exit(EXIT_FAILURE);
    }


    if(ftruncate(client_num_shm_fd, sizeof(int)) == -1){
        perror("ftruncate error : ");
        exit(EXIT_FAILURE);
    }
    if(ftruncate(sigKill_shm_fd, sizeof(int)) == -1){
        perror("ftruncate error : ");
        exit(EXIT_FAILURE);
    }


    client_num_shm = mmap(NULL, sizeof(int), PROT_READ \
                    | PROT_WRITE, MAP_SHARED, client_num_shm_fd, 0);
    
    if(client_num_shm == MAP_FAILED){
        perror("mmap failed : ");
        exit(EXIT_FAILURE);
    }

    sigKill_shm = mmap(NULL, sizeof(int), PROT_READ \
                    | PROT_WRITE, MAP_SHARED, sigKill_shm_fd, 0);
    
    if(sigKill_shm == MAP_FAILED){
        perror("mmap failed : ");
        exit(EXIT_FAILURE);
    }


    *client_num_shm = 0;
    *sigKill_shm = 0;

    struct sigaction sa;
    sa.sa_handler = handle_sigchld;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGCHLD, &sa, NULL) == -1){
        perror("sigaction failed : ");
        exit(EXIT_FAILURE);
    }

    

    printf(">> Server Started PID %d...\n",pid);
    printf("Waiting for clients...\n");

    if(create_dir(dir_name) != 0){
        if(errno == EEXIST){
            printf("Directory already exists\n");
        }
        else{
            perror("Error : ");
            printf("Failed to create directory!\n");
            exit(EXIT_FAILURE);
        }
       
    }


    snprintf(sv_log_path, 100, "%s%s%d%s",dir_name, "/logfile", pid,".txt");
    client_log_fd = create_file(sv_log_path);
    if(client_log_fd == -1){
        if(errno == EEXIST){
            printf("File %s already exists\n",sv_log_path);
        }
        else{
            printf("Failed to create logfile!\n");
            exit(EXIT_FAILURE);
        }
        
    }
    
    
    if(mkfifo(SERVER_FIFO,  S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        
        if(errno == EEXIST){
            printf("fifo %s already exists\n",SERVER_FIFO);
        }
        else {
            perror("Error : ");
            printf("Failed to create mkfifo!\n");
            exit(EXIT_FAILURE);
        }
    }
    

    server_fd = open(SERVER_FIFO, O_RDONLY);
    if(server_fd == -1){
        exit(EXIT_FAILURE);
    }
    
    dummy_fd1 = open(SERVER_FIFO, O_WRONLY);
    if(dummy_fd1 == -1){
        exit(EXIT_FAILURE);
    }

    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    
    waiting_QUE = queueInitialize(100);
    //fprintf(stderr, "%d",request.pid);

    
    for(;;){
                            
         if(*sigKill_shm == 1){

            // system automatically detach
            int i ;
            
            for (i = 0; i < *client_num_shm; i++) {
                kill(current_clients[i], SIGTERM);
            }
        
            exit(EXIT_SUCCESS);
        }
        if(read_file(server_fd, &request, sizeof(Request)) == -1){
            //fprintf(stderr, "Error reading request; discarding\n");
            
            if((*client_num_shm >= max_clients)){
                continue;    
            }
            
            
        }
        
        if(strcmp(request.msg, "Connect") == 0){
            
            enqueue(waiting_QUE,request.pid);
        }
        else if(strcmp(request.msg, "tryConnect") == 0){
            
            if(*client_num_shm < max_clients){
                enqueue(waiting_QUE,request.pid);
            }
            else{
                kill(request.pid, SIGTERM);
            }
        }
       
        
        if(*client_num_shm < max_clients && !is_empty(waiting_QUE)){
                curr_req_pid = dequeue(waiting_QUE);
                c_pid = fork();
                if(c_pid == 0) {
                    
                    current_clients[*client_num_shm] = curr_req_pid; // store client currently working
                    snprintf(client_req_fifo, CLIENT_FIFO_NAME_LEN ,CLIENT_REQUEST_FIFO_TEMPLATE, (long) curr_req_pid);
                    
                    client_req_fd = open(client_req_fifo, O_RDONLY);
                    if(client_req_fd == -1){
                            continue;
                    }
                    dummy_fd2 = open(client_req_fifo, O_WRONLY);
                    if(dummy_fd2 == -1){
                        exit(EXIT_FAILURE);
                    }
                    
                
                    
                    snprintf(client_res_fifo, CLIENT_FIFO_NAME_LEN,CLIENT_RESPONSE_FIFO_TEMPLATE, (long) curr_req_pid);
                    client_res_fd = open(client_res_fifo, O_WRONLY);
                    if(client_res_fd == -1){
                        continue;
                    }

                    snprintf(client_res_fifo_wr, CLIENT_FIFO_NAME_LEN,CLIENT_RESPONSE_FIFO_TEMPLATE_WR, (long) curr_req_pid);

                    client_res_fd_wr= open(client_res_fifo_wr, O_RDONLY);
                    
                    if(client_res_fd_wr == -1){
                        continue;
                    }

                    sem_wait(client_num_sem);
                    (*client_num_shm) ++;
                    sem_post(client_num_sem);


                    fprintf(stdout,">> Client PID %ld connected as client%d\n",curr_req_pid, *client_num_shm);
                    char log[1024];
                    while (1)
                    {   
                        
                        if(read_file(client_req_fd, &request, sizeof(Request))  == -1){
                            perror("Error ");
                            fprintf(stderr, "Error reading request; discarding2\n");
                            continue;
                        }
                        memset(log,'\0',1024);
                        strcpy(log,request.msg);
                        write_to_file(client_log_fd,1024,log);
                        if(strncmp(request.msg, "help", 4) == 0){
                            if(handleHelp(request, response , client_res_fd) == -1){
                                fprintf(stderr,"%s","Failed to handle command\n");
                            continue;
                            }    
                            
                        }
                        else if(strncmp(request.msg, "readF",5) == 0){
                            if(handle_readF(request, response, client_res_fd) == -1){
                                
                            }


                        }
                        else if(strncmp(request.msg, "writeT",6) == 0){
                            if(handle_writeT(request, response, client_res_fd, client_res_fd_wr) == -1){
                                
                            }
                        }


                        else if(strncmp(request.msg, "download", 7) == 0){
                            
                            int bytsdowload = handle_Dowload(request,response,client_res_fd);
                            
                            
                            
                        }

                        

                        else if(strncmp(request.msg, "upload", 6) == 0){
                            if(handle_Upload(request, response, client_res_fd_wr) == -1){

                            }
                        }

                        else if(strcmp(request.msg, "list") == 0){
                            if(handle_list(client_res_fd) == -1){

                            }

                        }
                        else if((strcmp(request.msg, "quit")) == 0){
                            //cleanUp(client_res_fd, client_res_fd_wr);
                            sem_wait(client_num_sem);
                            --(*client_num_shm);
                            sem_post(client_num_sem);
                            close(client_res_fd);
                            close(client_res_fd_wr);
                            close(client_req_fd);
                            fprintf(stderr,">> Client with %d pid disconnected\n",request.pid);
                            exit(EXIT_SUCCESS);
                        }
                        else if((strcmp(request.msg, "killServer")) == 0){
                            *sigKill_shm = 1;
                            break;
                    
                        }
                        else{
                            strncpy(response.package,"There is no such a command found\n",sizeof(Response));
                            write_to_file(client_res_fd, sizeof(Response), &response);
                            
                        } 
                    }
                }
                else if(c_pid > 0){
                    continue;
                }
                else{
                    //cleanup;
                }
            }
            else if(*client_num_shm >= max_clients){
                fprintf(stdout,">> Connection request PID %d... Que FULL\n",request.pid);
            }
           
        }  

        
        
        return 0;
        
    }

    


