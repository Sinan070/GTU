#include "signalsHandler.h"

void signalHandler(int signum){
    switch (signum)
    {
    case SIGKILL:
       
        printf("SIGKILL IS CATCHED\n");
        break;
    case SIGINT :
       
        printf("SIGINIT IS CATCHED\n");
    
        break;
    case SIGTSTP :
        printf("SIGTSTP IS CATCHED\n");
        break;        
    default:
        break;
    }
}

