#include"headers.h"

void foreground(char* token[])
{
  //  printf("foreground called");
    pid_t p_id;

    //create the child process
    p_id=fork();
    if(p_id<0)
    {
        perror("fork failed:");
        return;
    }

   /* strcpy(current_fore.name,token[0]);
    current_fore.pid=pid;*/

    if(p_id == 0)
    {
      //execute the child process
      setpgid(0, 0);
      int b = execvp(token[0],token);
      if(b<0)
      {
        perror("execvp error");
       
      }
      exit(0);
    }
    else
    {//used to store status  of child
      int status;
      childpid =p_id;
      foreground_job.pid=p_id;
      strcpy(foreground_job.name,token[0]);
      foreground_job.is_back=0;
      //0:wait for any child process
      waitpid(-1, NULL, WUNTRACED);
    }
}
