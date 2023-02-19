#include"headers.h"

void pinfo(char* token[],int arg_no)
{
    char pid_str[1000];
    if(arg_no == 1)
    {
        sprintf(pid_str,"%d",getpid());
    }
    else
    {
        strcpy(pid_str,token[1]);
    }
    char file_stat[1000],file_exe[1000],file_statm[1000];
    strcpy(file_stat,"/proc/");
    strcpy(file_exe,"/proc/");
    strcpy(file_statm,"/proc/");
    strcat(file_stat,pid_str);
    strcat(file_exe,pid_str);
    strcat(file_statm,pid_str);
    strcat(file_stat,"/stat");
    strcat(file_exe,"/exe");
    strcat(file_statm,"/statm");

    FILE *file_pointer;
    if((file_pointer=fopen(file_stat,"r"))==NULL)
    {
        printf("file doesn't exist\n");
        return;
    }

    int pid;
    char status;
    long int memory;
   
 
    fscanf(file_pointer,"%d",&pid);
    printf("pid -- %d\n", pid);

    char str[1000];
    fscanf(file_pointer,"%s",str);
    fseek(file_pointer,1,SEEK_CUR);
    fscanf(file_pointer,"%c",&status);
    printf("Process Status --- %c\n", status);
    fclose(file_pointer);

    //virtual memory size

    FILE *file_pointer_2;
    if((file_pointer_2=fopen(file_statm,"r"))==NULL)
    {
        perror("pinfo error:");
        return;
    }
    fscanf(file_pointer_2,"%ld",&memory);
    printf("Memory(virtual) --- %ld KB\n", memory);

    char path[1000];
    int x = readlink(file_exe,path,1000);
    path[x]='\0';
    
    int q;
    char dir[1000];
    char final_path[1000];

    if(strcmp(path,hdPath)==0)
    {
        strcpy(final_path,"~");
    }
    else
    {
        int flag=0;
        if(strlen(path)>strlen(hdPath))
        {
            
            for(int i=0;i<strlen(hdPath);i++)
            {
                if(path[i]!=hdPath[i])
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
            strcpy(final_path,"~");
            int ref=0;
            for(q=strlen(hdPath);path[q];q++)
            {
                dir[ref++]=path[q];
            }
            dir[ref]='\0';
            strcat(final_path,dir);
            }
            else
            {
                 strcpy(final_path,path);
            }
            

        }
        else
        {
            strcpy(final_path,path);
        }
        
    }
   

        
    printf("Executable Path---  %s\n",final_path);




}