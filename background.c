#include"headers.h"

void background(char *token[])
{
    //create the child process
    int pid=fork();
    
    if(pid<0)
    {
        perror("fork failed:");
        return;
    }
    childpid = pid;
    if(pid == 0)
    {
      setpgid(0,0);
      //execute the child process
      int ret_val_exec_child = execvp(token[0],token);
      if(ret_val_exec_child<0)
      {
        perror("execvp error");
       
      }
  
    }
    else
    {
        backgroundJob_count++;
        printf("[%d] %d\n",backgroundJob_count,pid);
    }
    bjob[backgroundJob_count].is_back = 1;
    strcpy(bjob[backgroundJob_count].name,token[0]);
    bjob[backgroundJob_count].pid=pid;
    return;

}