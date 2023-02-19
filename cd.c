#include "headers.h"

void cd(char* token[1000],int arg_no)
{
    char dir[10000];
    char cwd[10000];
    char lwd[10000];
    //get the current working directory

    getcwd(cwd,sizeof(cwd));
    
    if(arg_no > 2)
    {
        strcpy(lwd,cwd);
        char dir_path[1000];
        strcpy(dir_path,token[1]);
        for(int i=2;i<arg_no;i++)
        {
            strcat(dir_path," ");
            strcat(dir_path,token[i]);
        }
        int check= chdir(dir_path);
        if(check<0)
        {
            printf("invalid directory\n");
        }
        return;
    }

    //cd
    if(arg_no == 1)
    {
        strcpy(lwd,cwd);
        chdir(hdPath);
        return;
    }

    //cd .
    if(token[1][0] == '.' && strlen(token[1])==1)
    { 
        strcpy(lwd,cwd);
        chdir(cwd); 
        return;     
    }
    //cd -
    if(token[1][0] == '-' && strlen(token[1])==1)
    { 
        printf("%s\n",lwd);
        chdir(lwd); 
        return;     
    }
    //cd ~
    if(token[1][0] == '~' && strlen(token[1])==1)
    { 
        strcpy(lwd,cwd);
        chdir(hdPath);  
        return;
    }
    //cd ..
    if(token[1][0] == '.' && token[1][1] == '.' && strlen(token[1]) == 2)
    {
        strcpy(lwd,cwd);
         chdir("..");
         return;
    }
    
        
        int flag = chdir(token[1]);
        strcpy(lwd,cwd);
        if(flag<0)
        {
            perror("invalid directory");
            return;
        }

}