#include "my_utils.h"



int get_word_count(char* input){

    int word_count = 0;
    if(input != 0){
        char *token = strtok(input, " ");
        while (token != NULL && word_count < 3) {
            word_count++;
            token = strtok(NULL, " ");
        }
    }
    return word_count;
    
}

int sendFilePermission(void *buffer,int size, int dest_fd){
    return write_to_file(dest_fd, size, buffer);
}
mode_t getFilePermission(const char* filename){
    struct stat filestat ;

    
    // Get the file status information
    if (stat(filename, &filestat) == -1) {
        perror("stat");
        return 888;
    }


    // Extract the permission bits
    mode_t perm = filestat.st_mode & 0777;
    //fprintf(stderr, "%u", perm);

    return perm;

}

int create_dir(const char *dir_name){
    int status = mkdir(dir_name, 0777);
    return status;

}

int read_file(int fd, void * buf, int len){
    
    int bytesRead = -1;
    char *buffer = (char*)buf;    
    int totalbytes = 0;
    memset(buffer, '\0',len);
    while (totalbytes <len){
        if (bytesRead == 0) {
            // End of file, no more data to read
            break;
        }

        bytesRead = read(fd, buffer, len);
        
        totalbytes += bytesRead;

        
        if (bytesRead < 0) {
            
            perror("read");
            return -1;
        }
        
    }
    //fprintf(stderr,"%d",totalbytes);
    return totalbytes;
}

int read_file_into(const int fd , void *buffer, const int len, const int dest_fd){
    int totalbytes = 0;
    char *buf = (char*) buffer;
    int byteswritten = 0;
    int retval =0;
    int bytesread = -1;
    char *bp;
    
    for (; ;)
    {  
        memset(buf, '\0',len);    
        if(bytesread == 0){
            retval = 0;
            break;
        }

        bytesread = read(fd, buf, len);
        
        
        if(bytesread == -1){
            perror("ERror : ");
            retval = -1;
            break;
        }
        else if(bytesread == 0){
            break;
        }
        else if(strcmp(buf,"EOF") == 0){
            break;
        }
        else{
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
                perror("Error :");
                retval = -1;
                break;
            }

        }
    }
    if(retval != -1) retval = totalbytes;
    return retval;

}

int read_line_of_file_into(const int fd, void *buffer, const int len, const int lineNumber, const int dest_fd) {
   int totalbytes = 0;
char *buf = (char*) buffer;
int byteswritten = 0;
int retval = 0;
int bytesread;
char *bp;
int linenum = 0;   // The desired line number to read
int currline = 0;  // The current line number being read
int foundline = 0;  // Flag to indicate if the desired line has been found

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
        if (!foundline) {
            // Check if the current character is a newline
            if (*bp == '\n') {
                currline++;  // Increment the current line number
                if (currline == linenum) {
                    foundline = 1;  // Set flag to indicate that the desired line has been found
                }
            }
        } else {
            byteswritten = write(dest_fd, bp, 1);  // Write the current character to the output file
            if (byteswritten < 0){
                retval = -1;
                break;
            }
            totalbytes += byteswritten;
        }
        bytesread--;
        bp++;
        if (foundline && *bp == '\n') {
            // Stop reading the file once the desired line has been read completely
            retval = totalbytes;
            break;
        }
    }
    if (retval == -1){
        break;
    }
}
return retval;
}


int create_file(char *path){
   
    int status = open(path,  O_CREAT | O_RDWR, 0666);
    return status;

}


int isNumber(char *str){
    int i;
    int isNumber = 1;
    for(i = 0 ; str[i]!= '\0' && str[i] !=  '\n'   ; i++){
            if(!isdigit(str[i])){
                isNumber = 0;
            }
    }
    return isNumber;
}


int split_string_into(char *input, char ** words, int len){
    int word_count = 0;
    int retval;
    int i;
    int isNumber = 1;

    char *token = strtok(input, " ");
    while (token != NULL && word_count < 3) {
        if(word_count >= len){
            retval = -1;
            break;
        }
        strncpy(words[word_count], token, strlen(token));
        word_count++;
        token = strtok(NULL, " ");
    }
    retval = word_count; 
    return retval;
    
} 



int write_to_file(int fd, int len , void* buffer){

    int totalbytes = 0;
    char *ptr = (char*) buffer;
    int byteswritten = 0;
    int retval =0;
    while(totalbytes < len){
        byteswritten = write(fd, ptr, len);
            if(byteswritten == -1){
               
                retval = -1;
                break;
            }
        totalbytes += byteswritten;
        ptr += byteswritten;
    }
    return retval;
}