#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include<string.h>


int write_to_file(int fd, const void *buf, int count);

#endif