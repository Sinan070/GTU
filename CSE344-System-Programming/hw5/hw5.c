#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ftw.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/types.h>

typedef struct File_info{
    int destination_fd;
    int source_fd;
    char destination_fileName[4096];
    char source_fileName[4096];
    
}File_info;


File_info * file_buffer;

int bufferCount = 0;
int bufferFront = 0;
int bufferRear = 0;
int bufferSize;

int firstBase =0;
int done;
char  destDir[1024];
char sourceDir[1024];
int totalBytesCopied = 0;

// Define synchronization primitives
pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferNotFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferNotEmpty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t outputMutex =   PTHREAD_MUTEX_INITIALIZER; // Mutex for protecting the critical section


int traverse_directory(const char * directory );
void copyFile_info(File_info* source, File_info* dest);

// Signal handler function for SIGINT
void sigintHandler(int signum) {
    free(file_buffer);
    exit(EXIT_SUCCESS);
}


static int nftw_Callback(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    File_info file_info;
    char dir_name[2048];
    char fifo_name[2048];
    time_t startTime = time(NULL);
    if(startTime <= sb->st_mtime) return 0;
    
    
    if (firstBase == 0) {
        firstBase = ftwbuf->base;
    }


    if (tflag == FTW_D) {
        snprintf(dir_name, sizeof(dir_name), "%s/%s", destDir, (fpath + firstBase));
       
        mkdir(dir_name, sb->st_mode);
    } 
    else if (S_ISFIFO(sb->st_mode)) {
        snprintf(fifo_name, sizeof(fifo_name), "%s/%s", destDir, (fpath + firstBase));

        mkfifo(fifo_name, sb->st_mode);
    } else if (tflag == FTW_F) {
        snprintf(file_info.source_fileName, sizeof(file_info.source_fileName), "%s", fpath);
        file_info.source_fd = open(file_info.source_fileName, O_RDONLY);
        if (file_info.source_fd == -1) {
            fprintf(stderr, "Error opening source file %s\n", file_info.source_fileName);
            return 1;
        }
        
        snprintf(file_info.destination_fileName, sizeof(file_info.destination_fileName), "%s/%s", destDir, (fpath + firstBase));

        file_info.destination_fd = open(file_info.destination_fileName, O_CREAT | O_TRUNC | O_RDWR, sb->st_mode);
        if (file_info.destination_fd == -1) {
            fprintf(stderr, "Error opening destination file %s\n", file_info.destination_fileName);
            close(file_info.source_fd);
            return 1;
        }

        pthread_mutex_lock(&bufferMutex);
        while (bufferCount == bufferSize) {
            pthread_cond_wait(&bufferNotFull, &bufferMutex);
        }

        copyFile_info(&file_info, &file_buffer[bufferRear]);
        bufferCount++;
        bufferRear = (bufferRear + 1) % bufferSize;
        pthread_cond_signal(&bufferNotEmpty);
        pthread_mutex_unlock(&bufferMutex);
    }

    return 0;  // To tell nftw() to continue
}



void copyFile_info(File_info* source, File_info* dest){
    
    dest->source_fd = source->source_fd;


    strcpy(dest->source_fileName, source->source_fileName);
    
    dest->destination_fd = source->destination_fd;
    strcpy(dest->destination_fileName, source->destination_fileName);
}
int copyFile(File_info file_info) {

    char buffer[4096];
    char *bp;
    int bytesRead;
    int bytesWritten = 0;
    int totalBytes = 0;
    for(;;){

        bytesRead = read(file_info.source_fd, buffer, sizeof(buffer)); 
        if(bytesRead <=0){
            break;
        }         
        bp = buffer;
        while (bytesRead > 0)
        {
            bytesWritten = write(file_info.destination_fd, buffer, bytesRead);
            if(bytesWritten < 0) break;
            totalBytes += bytesWritten;
            bytesRead -= bytesWritten;
            bp += bytesWritten;
        }
        if(bytesWritten == -1) break;
    }
    

    close(file_info.source_fd);
    close(file_info.destination_fd);

      
    return totalBytes;
}



void* consumerThread(void* param) {
    while (1) {
        pthread_mutex_lock(&bufferMutex);
        while (bufferCount == 0 && !done) {
            pthread_cond_wait(&bufferNotEmpty, &bufferMutex);
        }

        if (done && bufferCount == 0) {
            pthread_mutex_unlock(&bufferMutex);
            pthread_exit(NULL);
        }
        

        File_info file_info;
        memcpy(&file_info, &file_buffer[bufferFront], sizeof(File_info));
        bufferFront = (bufferFront + 1) % bufferSize;
        bufferCount--;
        pthread_cond_signal(&bufferNotFull);
        pthread_mutex_unlock(&bufferMutex);
        int totalBytes = copyFile(file_info);
        pthread_mutex_lock(&outputMutex);
        totalBytesCopied += totalBytes;
        fprintf(stdout, "\nCopied %d bytes from %s to %s\n", totalBytes,file_info.source_fileName, file_info.destination_fileName);
        pthread_mutex_unlock(&outputMutex);


    }
    return NULL;
}



void * producerThread(void * args){

    char ** infos = (char **) args;


    memcpy(sourceDir,infos[0], 1024);
    memcpy(destDir, infos[1], 1024);

    traverse_directory(sourceDir);
    done = 1;
    pthread_cond_broadcast(&bufferNotEmpty);

    pthread_detach(pthread_self());

    return NULL;

}



int traverse_directory(const char * directory ){
    int flags = 0;
    flags |= FTW_PHYS;
    if(nftw(directory, nftw_Callback, 20 , flags) == 1){
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}




int main(int argc, char *argv[]){
    
    int num_consumers;
    pthread_t producer;
    pthread_attr_t attr;
    
    struct sigaction sa;
    memset(&sa, 0 , sizeof(sa));
    sa.sa_handler = &sigintHandler;
    sigaction(SIGINT, &sa, NULL);
    
    if (argc != 5) {
        printf("Usage: ./program_name <buffer_size> <num_consumers> <source_directory> <destination_directory>\n");
        return 1;
    }
    
    bufferSize = atoi(argv[1]);

    // Perform error checking for buffer size
    if (bufferSize <= 0) {
        printf("Invalid buffer size. Please enter a valid number.\n");
        return 1;
    }


    // Parse the number of consumer threads
    num_consumers = atoi(argv[2]);

    // Perform error checking for number of consumer threads
    if (num_consumers <= 0) {
        printf("Invalid number of consumer threads. Please enter a valid number.\n");
        return 1;
    }

    
    
   

    file_buffer = (File_info*)malloc(sizeof(File_info)* bufferSize);
    
   
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
   

    // Initialize the thread attributes
    pthread_attr_init(&attr);
    
    // Set the detach state attribute to make the thread detachable
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_create(&producer, &attr, producerThread, argv + 3);
    
    pthread_t consumers[num_consumers];
    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumerThread, NULL);
    }
   
    // Wait for consumer threads to complete
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }


     // Display the parsed values
    printf("\n\nBuffer size: %d\n", bufferSize);
    printf("Number of consumer threads: %d\n", num_consumers);
    printf("Source directory: %s\n", argv[3]);
    printf("Destination directory: %s\n", argv[4]);

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("\nTotal time taken: %f seconds\n", elapsed_time);
    pthread_mutex_destroy(&outputMutex);
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&bufferMutex);
    pthread_cond_destroy(&bufferNotEmpty);
    pthread_cond_destroy(&bufferNotFull);



    fprintf(stdout,"\nTOTAL BYTES COPIED %d\n", totalBytesCopied);


    free(file_buffer);


    return 0;
}