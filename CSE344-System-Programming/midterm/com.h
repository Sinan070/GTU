#ifndef __COM_H
#define __COM_H

#include <sys/types.h>
#



#define SERVER_FIFO "server_fifo/fifo_sv"
#define CLIENT_REQUEST_FIFO_TEMPLATE "client_req_fifos/req_fifo_cl.%ld" 
#define CLIENT_RESPONSE_FIFO_TEMPLATE "client_res_fifos/res_fifo_cl.%ld"
#define CLIENT_FIFO_NAME_LEN 256
#define REQUEST_LEN 256
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