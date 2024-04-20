#ifndef __MY_UTILITIES_H
#define __MY_UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>



int sendFilePermission(void *buffer,int size, int dest_fd);
mode_t getFilePermission(const char* filename);
int create_dir(const char *dir_name);
int read_file(int fd, void * buf, int len);
int read_file_into(const int fd , void *buffer, const int len, const int dest_fd);
int read_line_of_file_into(const int fd, void *buffer, const int len, const int lineNumber, const int dest_fd);
int create_file(char *path);
int write_to_file(int fd, int len , void* buffer);
int split_string_into(char *input, char ** words, int len);
int isNumber(char *str);
int get_word_count(char* str);


#endif