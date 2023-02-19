#include"headers.h"

void env(char* token[],int arg_no)
{
    printf("entered setenv arg_no = %d", arg_no);
     if(arg_no == 3)
     {
        // printf("2 args");
        int ret_val = setenv(token[0],token[1],1);
        if(ret_val<0)
        {
            perror("setenv:");
        }
        
     }
     else if(arg_no == 2)
     {
        // printf("2 args");
        int ret_val = setenv(token[0],"",1);
        if(ret_val<0)
        {
            perror("setenv:");
        }
        
     }
     else
     {
         printf("please provide the arguments in proper format\n");
     }
    

    return;
}

void unset(char* token[],int arg_no)
{
 //   printf("entered unsetenv");
   if(arg_no >= 2)
   {
       int ret_val;
       for(int i=2;i<=arg_no;i++)
       {
            ret_val = unsetenv(token[i-1]);
            if(ret_val<0)
            {
                perror("unsetenv:");
            }
       }
        
   }
   else
   {
       printf("please provide the arguments\n");
   }
   
   
    return;
}