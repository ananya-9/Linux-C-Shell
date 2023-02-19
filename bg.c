#include"headers.h"

void bg(char *token[],int arg_no)
{
    int process=atoi(token[1]);
    if(arg_no!=2)
    {
        printf("wrong no of arguments\n");
    }
    else
    {
        if(process <= backgroundJob_count)
        {
                pid_t pid=bjob[process].pid;
                kill(pid, SIGTTIN);
                kill(pid, SIGCONT);
        }
        else
        {
            printf("job is invalid\n");
        }
        
    }
    
}