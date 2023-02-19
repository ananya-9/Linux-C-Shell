#include"headers.h"

void kjob(char *token[],int arg_no)
{
    if(arg_no != 3)
    {
        printf("please provide proper arguments\n");
        return;
    }
    int process=atoi(token[1]);
    int sig=atoi(token[2]);
    if(process<=backgroundJob_count)
    {
        kill(bjob[process].pid, sig);
    }
    else
    {
        printf("invalid job\n");
    }
    return;
}