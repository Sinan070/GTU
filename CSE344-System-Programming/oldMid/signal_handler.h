#ifndef __HANDLE_SIGCHILD_H
#define __HANDLE_SIGCHILD_H
#include <sys/wait.h>
void handle_sigchld(int sig);

#endif