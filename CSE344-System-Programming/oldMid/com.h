#ifndef __COM_H
#define __COM_H

#include <sys/types.h>
#



#define SERVER_FIFO "/tmp/fifo_sv"
#define CLIENT_REQUEST_FIFO_TEMPLATE "/tmp/req_fifo_cl.%ld" 
#define CLIENT_RESPONSE_FIFO_TEMPLATE "/tmp/res_fifo_cl.%ld"
#define CLIENT_RESPONSE_FIFO_TEMPLATE_WR "/tmp/res_fifo_cl_wr.%ld"
#define CLIENT_FIFO_NAME_LEN 256
#define REQUEST_LEN 1024
#define RESPONSE_LEN 4096

typedef struct  request
{
    pid_t pid;
    char msg[REQUEST_LEN];
}Request;

typedef struct response{
    char package[RESPONSE_LEN];
}Response;









#endif