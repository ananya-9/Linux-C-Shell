#include"headers.h"

int check_p(char *str,char c)
{
    //input redirection
    
    if(c=='i')
    {
       // printf("enetered input redirection\n");
        for(int i=0;str[i]!='\0';i++)
        {
            if(str[i]=='<')
            {
                return 1;
            }
        }

        return 0;
    }
    //output redirection
    if(c=='o')
    {
        //  printf("enetered output redirection\n");
         for(int i=0;str[i]!='\0';i++)
        {
            if(str[i]=='>')
            {
                return 1;
            }
        }
        return 0;
    }

}

void pipe_function(char *buf)
{

    //variable declarations
    char ***command_string = (char***)malloc(sizeof(char**)*100);
    int no,i,j,k,l;
    char *rest_array;
    char *tkn_array;
    char*token;
    char *rest;
    pid_t pid;
    char *temp;
    char *s[1000];
    

    //doing it only once since each time of pipe it is called
    tkn_array = strtok_r(buf,"|",&rest_array);
    i=0;//for the ith tokenarr
    no=0;
    //loop for storing all commands in 3d array
    while(tkn_array!=NULL)
    {
        command_string[i] = (char**)malloc(sizeof(char*)*100);
        token=strtok_r(tkn_array," \n\t\r",&rest);
        j=0;
        while(token!=NULL)
        {
            command_string[i][j]=(char*)malloc(sizeof(char)*100);
            strcpy(command_string[i][j],token);
            j++;
            token=strtok_r(NULL," \n\t\r",&rest);
        }
        command_string[i][j]=NULL;
        tkn_array = strtok_r(NULL,"|",&rest_array);
        i++;
        no++;
    }
    command_string[i]=NULL;

    //loop for piping
    int fp[2];
    int p=0,fp_input=0;
    int ss;

    while(*command_string !=NULL)
    {
        pipe(fp);
        pid =fork();
        ss=dup(STDOUT_FILENO);

        if(pid == 0)
        {   
            dup2(fp_input,0);
            if(p!=(no-1))
            {
                dup2(fp[1],1);
            }
            close(fp[0]);

            if(check_p((*command_string)[0],'i'))
            {
                char *ip[2];
                ip[0]=strtok((*command_string)[0],"<");
                ip[1]=strtok(NULL,"<");

                temp=strtok(ip[0]," \n\t\r");
                l=0;
                while(temp!=NULL)
                {
                    strcpy(s[l++],temp);
                    temp=strtok(NULL," \n\t\r");
                }
                char *command[l+1];
                for(int i=0;i<l;i++)
                {
                    command[i]=s[i];
                }
                command[i]=NULL;

                char *temp2 =strtok(ip[1]," \n\t\r");
                while(temp2!=NULL)
                {
                    int fd = open(temp2,O_RDONLY);
                    if(fd<0)
                    {
                        printf("file doesnt exist\n");
                        return;
                    }
                    else
                    {
                        dup2(fd,0);
                    }
                    
                
                if(execvp(command[0],command)==-1)
                {
                     dup2(ss,1);
                    printf("command is incorrect\n");
                   
                }
                }
                
            }
            if(check_p((*command_string)[0],'o'))
            {
                char *op[2];
                op[0]=strtok((*command_string)[0],">");
                op[1]=strtok(NULL,">");

                temp=strtok(op[0]," \n\t\r");
                l=0;
                while(temp!=NULL)
                {
                    strcpy(s[l++],temp);
                    temp=strtok(NULL," \n\t\r");
                }
                char *command[l+1];
                for(int i=0;i<l;i++)
                {
                    command[i]=s[i];
                }
                command[i]=NULL;

                char *temp2 =strtok(op[1]," \n\t\r");
                while(temp2!=NULL)
                {
                    int fo = open(temp2,O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                    dup2(fo, 1);
                if(execvp(command[0],command)==-1)
                {
                     dup2(ss,1);
                    printf("command is incorrect\n");
                   
                }
                }

            }
            else
            {
                if(execvp((*command_string)[0],*command_string)== -1)
                {
                    dup2(ss, 1);
                    printf("plese give proper command\n");
                }
                return;
            }
            


        }
        else if(pid == -1)
        {
            printf("error forking\n");
            return;
        }
        else
        {   
            wait(NULL);
            close(fp[1]);
            fp_input = fp[0];
            p++;
            command_string++;
            
        }
        
        
        
    }

}