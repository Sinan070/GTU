#define _POSIX_SOURCE
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

int write_to_fifo(int fd, int len , void* buffer);
int split_string_into(char *input, char ** words);
int create_server_dir(const char *dir_name){
    int status = mkdir(dir_name, 0777);
    return status;

}

int read_file(int fd, void * buf, int len){
    int bytesRead = 0;
    char *buffer;
    

    while (bytesRead = read(fd, buffer, len) != 0){
        if (bytesRead <= 0){
            break;
        }
        if(bytesRead == 0){
            return bytesRead;
        }
    }
    return -1;
}

int read_file_into(const int fd , void *buffer, const int len, const int dest_fd){
    int totalbytes = 0;
    char *buf = (char*) buffer;
    int byteswritten = 0;
    int retval =0;
    int bytesread;
    char *bp;
    
    fprintf(stderr,"%s","gecti5");
    for (; ;)
    {
        bytesread = read(fd, buf, len);
        if(bytesread <=0){
            retval = -1;
            break;
        }
        bp = buf;
        while (bytesread > 0)
        {
            byteswritten = write(dest_fd, bp, bytesread);
            if(byteswritten < 0){
                retval = -1;
                break;
            }
            totalbytes += byteswritten;
            bytesread -= byteswritten;
            bp += byteswritten;
        }
        if(byteswritten == -1){
            retval = -1;
            break;
        }
    }
    if(byteswritten =! -1) retval = byteswritten;

    return retval;

   
}

int read_line_of_file_into(const int fd, void *buf, const int len, const int lineNumber, const int dest_fd) {
    ssize_t nread;
    int current_line = 0;
    off_t offset = 0;
    int i;
    char *buffer = (char*)buf;

    memset(buffer,'\0',len);
    while ((nread = read(fd, buffer, len)) > 0) {
        for (i = 0; i < nread; i++) {
            if (buffer[i] == '\n') {
                current_line++;
            }
            if (current_line == lineNumber) {
                
                if (write(dest_fd, buffer, i+1) != i+1) {
                    perror("write");
                    return -1;
                }
                if (close(fd) == -1) {
                    perror("close");
                    return -1;
                }
                return 0;
            }
        }
        offset += nread;
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("lseek");
            return -1;
        }
    }

    if (nread == -1) {
        perror("read");
        return -1;
    }

    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    return 0;
}


int create_log_file(char *path){
   
    int status = open(path,  O_CREAT | O_RDWR, 0777);
    return status;

}
int handleHelp(const Request request, Response response, const int client_res_fd){
    int retval = 0;
            
            if(strcmp(request.msg , "help\n" ) == 0){
                strncpy(response.package, "\tAvaliable Comments are:\nhelp, list, readF, writeT, upload, download, quit, killServer\n",sizeof(Response));
                //fprintf(stderr,"%s",response.package);
                //fprintf(stdout,"%s","HELP REQUEST IS CAME\n ");
                //fflush(stdout);
            }
            
            else if(strcmp(request.msg, "help readF\n") == 0){
                strncpy(response.package, "readF <file> <line #>\n\trequests to display the # line of the <file>,"\
                "if no line number is given\n\t"\
                "the whole contents of the file is requested (and displayed on the client side)\n",sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help writeF\n") == 0){
                strncpy(response.package, "writeT <file> <line #> <string>\n\t"\
                "request to write the content of “string” to the #th line the <file>, if the line # is not given\n\t"\
                "writes to the end of file. If the file does not exists in Servers directory creates and edits the\n\t"\
                "file at the same time"
                ,sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help list\n") == 0){
                strncpy(response.package, "-list\n\tSends a request to display the list of files in Servers directory\n",sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help upload\n") == 0){
                strncpy(response.package, "upload <file>\n\t"\
                "uploads the file from the current working directory of client to the Servers directory\n\t"\
                "(beware of the cases no file in clients current working directory and file with the same\n\t"
                "name on Servers side)\n"
                ,sizeof(Response));
                
            }
            else if(strcmp(request.msg, "help dowload\n") == 0){
                strncpy(response.package,"download <file>\n\trequest to receive <file> from Servers directory to client side\n",sizeof(Response));
            }
            else if(strcmp(request.msg, "help quit\n") == 0){
                strncpy(response.package,"quit\n\tSend write request to Server side log file and quits\n",sizeof(Response));
    
            }
            else if(strcmp(request.msg, "help killserver\n") == 0){
                strncpy(response.package,"killServer\n\tSends a kill request to the Server\n",sizeof(Response));

            }
            else {
                fprintf(stderr,"%s","There is no such a command found\n");
                retval = -1;
                return retval;
            }
            if(write_to_fifo(client_res_fd, sizeof(response), &response ) == -1){
                retval = -1;
            }

    return retval;

}
int handle_readF(Request request, Response response, const int client_res_fd){
    char *words[3];
    int i ;
    int retval = 0;
    int fd;
    int word_count = 0;
    
    fprintf(stderr,"%s","gecti0");
    
    for(i = 0 ; i < 3; ++i ){
        words[i] = (char *) malloc(sizeof(char)* 256);
    }

    fprintf(stderr,"%s","gecti1");
    word_count = split_string_into(request.msg, words);
    if( word_count == -1){
        retval = -1;
        //fprintf(stderr,"%s","gecti2");
    }
    //fprintf(stderr,"%d",word_count);
    
    for (i = 0; i < word_count; i++)
    {
        fprintf(stderr, "%s ", words[i]);
    }
    int len = strlen(words[1]);
    words[1][len-1] = '\0';
    //fprintf(stderr,"%s",);

    if(retval != -1){
        fd = open(words[1], O_RDONLY);
        if(fd == -1){
            retval = -1;
        }
        else{
            fprintf(stderr,"%s","gecti6");
            if(word_count == 2){
                fprintf(stderr,"%s","gecti6");
                if(read_file_into(fd, &response, sizeof(Response), client_res_fd) == -1){
                    retval = -1;
                }
            }
            else if(word_count == 3){
                fprintf(stderr,"%s","gecti7");
                int line_num = atoi(words[2]);
                if(read_line_of_file_into(fd, &response, sizeof(Response), line_num, client_res_fd)){
                    retval = -1;
                }
            }
        }

    }
    close(fd);
    return retval;

} 


int split_string_into(char *input, char ** words){
    int word_count = 0;
    int retval;
    int i;
    int isNumber = 1;

    char *token = strtok(input, " ");
    while (token != NULL && word_count < 3) {
        strncpy(words[word_count], token, strlen(token));
        word_count++;
        token = strtok(NULL, " ");
    }
    if(word_count == 3){
        for(i = 0 ; words[2][i]!= '\0' && words[2][i]!= '\n'   ; i++){
            if(!isdigit(words[2][i])){
                isNumber = 0;
            }
        }
        
    }
    if ((word_count == 2 || (word_count == 3 && isNumber))) {
        retval = word_count;
        fprintf(stderr,"RETVALAQ%d",retval);
        
    }
    else retval = -1;

    return retval;
    
} 



int write_to_fifo(int fd, int len , void* buffer){

    int totalbytes = 0;
    char *ptr = (char*) buffer;
    int byteswritten = 0;
    int retval =0;
    while(totalbytes < len){
        while(((byteswritten = write(fd, ptr, len)) == -1) && errno == EINTR){};
            if(byteswritten == -1){
               
                retval = -1;
                break;
            }
        totalbytes += byteswritten;
        ptr += byteswritten;
    }
    return retval;
}




int main(int argc, char *argv[]){

    char sv_log_path[100];
    char client_req_fifo[128];
    char client_res_fifo[128];
    char *dir_name = argv[1];
    int max_clients = atoi(argv[2]);
    int server_fd;
    int dummy_fd1;
    int dummy_fd2;
    int client_num = 0;
    int client_req_fd;
    int client_res_fd;
    
    int c_pid;
    int wait_number = 0;


    long int curr_req_pid;
    Request request;
    Response response;
    sigset_t set;
    int num_read;
    int num_write;
    Queue * waiting_QUE;
    
    //Request request_queue[max_clients];

    __pid_t pid = getpid();

    umask(0);

    printf(">> Server Started PID %d...\n",pid);
    printf("Waiting for clients...\n");

    if(create_server_dir(dir_name) != 0){
        if(errno == EEXIST){
            printf("Directory already exists\n");
        }
        else{
            printf("Failed to create directory!\n");
            exit(EXIT_FAILURE);
        }
       
    }


    snprintf(sv_log_path, 100, "%s%s%d%s",dir_name, "/logfile", pid,".log");
    
    if(create_log_file(sv_log_path) == -1){
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
    //fprintf(stderr, "%s","GECTI");
    
    waiting_QUE = queueInitialize(100);
    for(;;){
            
        if(read(server_fd, &request, sizeof(Request)) != sizeof(Request)){
            fprintf(stderr, "Error reading request; discarding\n");
            continue;
        }
        
        
    
        
        if(strcmp(request.msg, "Connect") == 0){
            enqueue(waiting_QUE,request.pid);
            
            if(client_num < max_clients){
                curr_req_pid = dequeue(waiting_QUE);
                
                snprintf(client_req_fifo, CLIENT_FIFO_NAME_LEN ,CLIENT_REQUEST_FIFO_TEMPLATE, (long) curr_req_pid);
                if(mkfifo(client_req_fifo,  S_IRUSR | S_IWUSR | S_IWGRP) == -1){
                    if(errno == EEXIST){
                        printf("mkfifo %s already exists\n",client_req_fifo);
                    }
                    else {
                        printf("Failed to create mkfifo!\n");
                        exit(EXIT_FAILURE);
                    }
                }
                
                
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
               
                ++client_num;
                fprintf(stdout,">> Client PID %ld connected as client%d\n",curr_req_pid, client_num);
                c_pid = fork();
                
            }
           
        }  
        else if(strcmp(request.msg, "tryConnect") == 0){
            //send to process to terminate;
            /*if(client_num >= max_clients){

            }
            else{
                
                snprintf(client_fifo, CLIENT_FIFO_NAME_LEN,"%s%ld" ,CLIENT_FIFO_TEMPLATE, (long) request.pid);
                client_fd = open(client_fifo, O_WRONLY);
                if(client_fd == -1){
                    continue;
                }
                ++client_num;
                c_pid = fork();
                
            }*/
        }
        if(c_pid == 0) {
        
            while (1)
            {   
                if(read(client_req_fd, &request, sizeof(Request)) != sizeof(Request)){
                    fprintf(stderr, "Error reading request; discarding\n");
                    continue;
                }
                
                memset(&response, '\0', sizeof(Response) );

                //fprintf(stderr,"%s",request.msg);  
                /* code */
            //    sleep(10);
                if(strncmp(request.msg, "help", 4) == 0){
                    if(handleHelp(request, response , client_res_fd) == -1){
                    fprintf(stderr,"%s","Failed to handle command\n");
                    continue;
                    }    
                }
                else if(strncmp(request.msg, "readF",5) == 0){
                    fprintf(stderr,"%s","gecti");
                    if(handle_readF(request, response, client_res_fd) == -1){
                        
                    }


                }




                    
                
                
            }
            
            
            

        }
        else if(c_pid > 0){
            
            continue;
        }
        else{

        }
        
        

        
    }



    return 0;

}
