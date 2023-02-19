#include"headers.h"

void ls(char* token[],int arg_no)
{
    char curr_working_dir[1000];
    getcwd(curr_working_dir,sizeof(curr_working_dir));
    //ls
    if(arg_no == 1)
    {
      //  printf("entered loop");
        DIR *d;
        struct dirent **read;
        int x=0,count;
        count=scandir(curr_working_dir,&read,NULL,alphasort);
        if(count<0)
        {
            perror("no file exists");
            return;
        }
        else
        {
            while(x<count)
            {
                     if (read[x]->d_name[0] == '.')
                    {
                            x++;
                            continue;
                    }
                    else
                    {
                        printf("%s\n", read[x]->d_name);
                      x++;
                    }
                    
            }
        }

    }
    else if (arg_no == 2 && strcmp(token[1], "-a") == 0)
    {  
        
        DIR *d;
        struct dirent **read;
        int i=0,count;
        count=scandir(curr_working_dir,&read,NULL,alphasort);
        if(count<0)
        {
            perror("no file exists");
            return;
        }
        else
        {
            for(i=0;i<count;i++)
                printf("%s\n", read[i]->d_name);
        }
    }

    else if (arg_no == 2 && strcmp(token[1], "-l") == 0)
    {
           
        DIR *d;
        struct dirent **read;
        int x=0,count;
        count=scandir(curr_working_dir,&read,NULL,alphasort);
        if(count<0)
        {
            perror("no file exists");
            return;
        }
        else
        {
            while(x<count)
            {
                    char path[1000];
                    strcpy(path, read[x]->d_name);
                    x++;
                    struct stat s;
                    if(path[0]=='.')
                    {
                        continue;
                    }
                    else
                    {
                        char path_temp[1000];
                        strcpy(path_temp,curr_working_dir);
                        strcat(path_temp,"/");
                        strcat(path_temp,path);
                        stat(path_temp,&s);
                        char permission[20]="";
                        char date[30],time[6],u[10],own[10];
                        long long int link,size;
                        link=s.st_nlink;
                        struct passwd *pd;
                        pd = getpwuid(s.st_uid);
                        struct group *gr;
                        gr = getgrgid(s.st_gid);
                        size=s.st_size;
                        if (S_ISDIR(s.st_mode) ? strcat(permission, "d") : strcat(permission, "-"));
                        if ((s.st_mode & S_IRUSR) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWUSR) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXUSR) ? strcat(permission, "x") : strcat(permission, "-"));
                        if ((s.st_mode & S_IRGRP) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWGRP) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXGRP) ? strcat(permission, "x") : strcat(permission, "-"));
                        if ((s.st_mode & S_IROTH) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWOTH) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXOTH) ? strcat(permission, "x") : strcat(permission, "-"));
                        strftime(date, 24, "%Y-%m-%d    %H:%M", localtime(&(s.st_ctime)));
                        printf("%-12s%-6lld%-8s%-8s%-8lld%-24s%-20s\n", permission, link, pd->pw_name, gr->gr_name, size, date, path);
        
                    }
                }
            }
        }

        else if (arg_no && ((strcmp(token[1], "-la") == 0) || strcmp(token[1], "-al") == 0))
        {
            // printf("lsal");
            DIR *d;
            struct dirent **read;
            int x=0,count;
            count=scandir(curr_working_dir,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            else
            {
                while(x<count)
                {
                    char path[1000];
                    strcpy(path, read[x]->d_name);
                    x++;
                    struct stat s;
                    char path_temp[1000];
                    strcpy(path_temp,curr_working_dir);
                    strcat(path_temp,"/");
                    strcat(path_temp,path);
                    stat(path_temp,&s);
                    char permission[20]="";
                    char date[30],time[6],u[10],own[10];
                    long long int link,size;
                    link=s.st_nlink;
                    struct passwd *pd;
                    pd = getpwuid(s.st_uid);
                    struct group *gr;
                    gr = getgrgid(s.st_gid);
                    size=s.st_size;
                    if (S_ISDIR(s.st_mode) ? strcat(permission, "d") : strcat(permission, "-"));
                    if ((s.st_mode & S_IRUSR) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWUSR) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXUSR) ? strcat(permission, "x") : strcat(permission, "-"));
                    if ((s.st_mode & S_IRGRP) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWGRP) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXGRP) ? strcat(permission, "x") : strcat(permission, "-"));
                    if ((s.st_mode & S_IROTH) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWOTH) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXOTH) ? strcat(permission, "x") : strcat(permission, "-"));
                    strftime(date, 24, "%Y-%m-%d    %H:%M", localtime(&(s.st_ctime)));
                    printf("%-12s%-6lld%-8s%-8s%-8lld%-24s%-20s\n", permission, link, pd->pw_name, gr->gr_name, size, date, path);
        
                }
            }
        
        }
        else if(arg_no == 2 && strcmp(token[1], ".") == 0)
        {   
            DIR *d;
            struct dirent **read;
            int x=0,count;
            count=scandir(curr_working_dir,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            else
            {
                while(x<count)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                            x++;
                            continue;
                    }
                    else
                    {
                        printf("%s\n", read[x]->d_name);
                        x++;
                    }
                }
            }

        }
        else if(arg_no == 2 && strcmp(token[1], "..") == 0)
        {
            char temporary_path[1001];
            strcpy(temporary_path,curr_working_dir);
            chdir("..");
            getcwd(curr_working_dir,sizeof(curr_working_dir));
            DIR *d;
            struct dirent **read;
            int x=0,count;
            count=scandir(curr_working_dir,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            else
            {
                while(x<count)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        x++;
                        continue;
                    }
                    else
                    {
                        printf("%s\n", read[x]->d_name);
                        x++;
                    }
                }
            }
            chdir(temporary_path);


        }
        else if(arg_no == 2 && strcmp(token[1], "~") == 0)
        {
            DIR *d;
            struct dirent **read;
            int x=0,count;
            count=scandir(hdPath,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            else
            {
                while(x<count)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        x++;
                        continue;
                    }
                    else
                    {
                        printf("%s\n", read[x]->d_name);
                        x++;
                    }
                }
            }
        }
        else if(arg_no == 2)
        {    
            char temporary_path[1001];
            strcpy(temporary_path,curr_working_dir);
            chdir(token[1]);
            getcwd(curr_working_dir,sizeof(curr_working_dir));
            DIR *d;
            struct dirent **read;
            int x=0,count;
            count=scandir(curr_working_dir,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            else
            {
                while(x<count)
                {
                    if (read[x]->d_name[0] == '.')
                    {
                        x++;
                        continue;
                    }
                    else
                    {
                        printf("%s\n", read[x]->d_name);
                        x++;
                    }
                }
            }
            chdir(temporary_path);
        }
        else if(arg_no == 3)
        {
            char temporary_path[1001];
            strcpy(temporary_path,curr_working_dir);
            chdir(token[1]);
            getcwd(curr_working_dir,sizeof(curr_working_dir));
            struct dirent **read;
            int x=0,count;
            count=scandir(curr_working_dir,&read,NULL,alphasort);
            if(count<0)
            {
                perror("no file exists");
                return;
            }
            if(strcmp(token[2],"-a")==0)
            {
                while(x<count)
                {
                    printf("%s\n", read[x]->d_name);
                    x++;
                
                }
            }
            else if(strcmp(token[2],"-l")==0)
            {
                while(x<count)
                {
                    char path[1000];
                    strcpy(path, read[x]->d_name);
                    x++;
                    struct stat s;
                    if(path[0]=='.')
                    {
                        continue;
                    }
                    else
                    {
                        char path_temp[1000];
                        strcpy(path_temp,curr_working_dir);
                        strcat(path_temp,"/");
                        strcat(path_temp,path);
                        stat(path_temp,&s);
                        char permission[20]="";
                        char date[30],time[6],u[10],own[10];
                        long long int link,size;
                        link=s.st_nlink;
                        struct passwd *pd;
                        pd = getpwuid(s.st_uid);
                        struct group *gr;
                        gr = getgrgid(s.st_gid);
                        size=s.st_size;
                        if (S_ISDIR(s.st_mode) ? strcat(permission, "d") : strcat(permission, "-"));
                        if ((s.st_mode & S_IRUSR) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWUSR) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXUSR) ? strcat(permission, "x") : strcat(permission, "-"));
                        if ((s.st_mode & S_IRGRP) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWGRP) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXGRP) ? strcat(permission, "x") : strcat(permission, "-"));
                        if ((s.st_mode & S_IROTH) ? strcat(permission, "r") : strcat(permission, "-"));
                        if ((s.st_mode & S_IWOTH) ? strcat(permission, "w") : strcat(permission, "-"));
                        if ((s.st_mode & S_IXOTH) ? strcat(permission, "x") : strcat(permission, "-"));
                        strftime(date, 24, "%Y-%m-%d    %H:%M", localtime(&(s.st_ctime)));
                        printf("%-12s%-6lld%-8s%-8s%-8lld%-24s%-20s\n", permission, link, pd->pw_name, gr->gr_name, size, date, path);
        
                    }
                     
                
                }
           
            }
            else if((strcmp(token[2], "-la") == 0 )|| (strcmp(token[2], "-al") == 0))
            {
                while(x<count)
                {
                    char path[1000];
                    strcpy(path, read[x]->d_name);
                    x++;
                    struct stat s;
                    char path_temp[1000];
                    strcpy(path_temp,curr_working_dir);
                    strcat(path_temp,"/");
                    strcat(path_temp,path);
                    stat(path_temp,&s);
                    char permission[20]="";
                    char date[30],time[6],u[10],own[10];
                    long long int link,size;
                    link=s.st_nlink;
                    struct passwd *pd;
                    pd = getpwuid(s.st_uid);
                    struct group *gr;
                    gr = getgrgid(s.st_gid);
                    size=s.st_size;
                    if (S_ISDIR(s.st_mode) ? strcat(permission, "d") : strcat(permission, "-"));
                    if ((s.st_mode & S_IRUSR) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWUSR) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXUSR) ? strcat(permission, "x") : strcat(permission, "-"));
                    if ((s.st_mode & S_IRGRP) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWGRP) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXGRP) ? strcat(permission, "x") : strcat(permission, "-"));
                    if ((s.st_mode & S_IROTH) ? strcat(permission, "r") : strcat(permission, "-"));
                    if ((s.st_mode & S_IWOTH) ? strcat(permission, "w") : strcat(permission, "-"));
                    if ((s.st_mode & S_IXOTH) ? strcat(permission, "x") : strcat(permission, "-"));
                    strftime(date, 24, "%Y-%m-%d    %H:%M", localtime(&(s.st_ctime)));
                    printf("%-12s%-6lld%-8s%-8s%-8lld%-24s%-20s\n", permission, link, pd->pw_name, gr->gr_name, size, date, path);
        
                }
            }
        
            chdir(temporary_path);
        }
        else
        {
            printf("Too many arguments\n");
        }
    
    
    }
