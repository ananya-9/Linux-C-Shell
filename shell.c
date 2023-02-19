#include"headers.h"

job bjob[1000];
job foreground_job;
int backgroundJob_count=0;
int shellid =0;
int childpid=-1;
int mode;
struct utsname uinfo;

void print_pmt(char *username,char *sysname)
{
    char cwd[1000];
    getcwd(cwd,sizeof(cwd));
    strcpy(pmt,"<");
    strcat(pmt,username);
    strcat(pmt,"@");
    strcat(pmt,sysname);
    strcat(pmt,":");

   int q;
   char dir[1000];
   int flag = 0;

    if(strcmp(cwd,hdPath)==0)
    {
        strcat(pmt,"~");
    }
    else
    {

       // printf("strlen of cwd is %ld\n",strlen(cwd));
       // printf("strlen of home dir is %ld\n",strlen(hdPath));
        if(strlen(cwd)>strlen(hdPath))
        {
            for(int i=0;i<strlen(hdPath);i++)
            {
                if(cwd[i]!=hdPath[i])
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
            strcat(pmt,"~");
            int ref=0;
            for(q=strlen(hdPath);cwd[q];q++)
            {
                dir[ref++]=cwd[q];
            }
            dir[ref]='\0';
            strcat(pmt,dir);
            }
            else
            {
                strcat(pmt,cwd);
            }


        }
        else
        {
            strcat(pmt,cwd);
        }

    }

    strcat(pmt,">");
    printf("%s",pmt);
}

int check(char *token,char c)
{   //redirection
    if(c=='r')
    {
        int len=strlen(token);
        for(int i=0;i<len;i++)
        {
            if (token[i] == '<' || (token[i] == '>' && token[i + 1] != '>'))
                return 2;
            if (token[i] == '>' && token[i + 1] == '>')
                return 3;
        }
        return 0;
    }
    //pipe
    if(c=='p')
    {
        int len = strlen(token);
        for(int i=0;i<len;i++)
        {
             if(token[i] == '|')
            {
                return 1;
            }
        }
        return 0;
    }
}
void child_sig(int signo)
{
    pid_t pid;
    int status;
    pid=waitpid(WAIT_ANY,&status,WNOHANG);
    for(int i=1;i<=backgroundJob_count;i++)
    {
        if(bjob[i].pid==pid)
        {
            if(WEXITSTATUS(status)==0)
            {
                printf("\n%s whose pid %d exited normal\n",bjob[i].name,bjob[i].pid);
            }
            else
            {
                printf("\n%s whose pid %d exited with status %d\n",bjob[i].name,bjob[i].pid,WEXITSTATUS(status));
            }
            print_pmt(uinfo.nodename,uinfo.sysname);
            fflush(stdout);
            break;
        }
    }
    signal(SIGCHLD,child_sig);
}

void ctrl_c(int signo)
{
    pid_t pid;
    pid=getpid();
    if(pid==shellid)
    {
        if(childpid!=-1)
        {
            kill(childpid,SIGINT);
        }
        signal(SIGINT,ctrl_c);
    }
}

void ctrl_z(int signo)
{
    pid_t pid;
    pid =getpid();
    if(pid==shellid)
    {
        if(childpid!=-1)
        {
            kill(childpid,SIGTTIN);
            kill(childpid,SIGTSTP);
            backgroundJob_count++;
            bjob[backgroundJob_count].is_back=1;
            bjob[backgroundJob_count].pid=childpid;
            strcpy(bjob[backgroundJob_count].name,foreground_job.name);

        }
        signal(SIGTSTP,ctrl_z);
    }
}

int main(int argc,char *argv)
{
    shellid= getpid();

    //code to get the username and systemname
    char* username = (char *)malloc(100*sizeof(char));
    char* sysname = (char *)malloc(100*sizeof(char));
    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid ();
    pw = getpwuid (uid);
    if (uname(&uinfo) != 0)
    {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    if (!pw)
    {
        printf("error in getting the username\n");
        return 0;
    }
    strcpy(username,pw->pw_name);
    gethostname(sysname,sizeof(sysname));

    //getting the home directory
    if (getcwd(hdPath, sizeof(hdPath)) == NULL)
    {
        perror("getcwd() error");
       return 0;
    }
    //print pmt
    print_pmt(username,sysname);

    //variables for taking input
    size_t size_i = 100;
    char* input_str = (char *)malloc(size_i*sizeof(char));
    char *tkn_array[1000];

    while(1)
    {
        childpid = -1;

        //taking input
        if(getline(&input_str,&size_i,stdin)==-1)
        {
            printf("error\n");
            return 0;
        }

        //handling the segmentation fault
        if (strcmp(input_str, "\n") == 0)
        {
             print_pmt(username,sysname);
            continue;
        }

   //signal(SIGCHLD, SIG_IGN);
//signal(SIGCHLD, child_signal);
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
        //tokenizing into semicolon
        char *tkn_array[1000];
        char *rest_arr = input_str;
        int num_of_semicolons=0;
        while(tkn_array[num_of_semicolons]=strtok_r(rest_arr,";",&rest_arr))
        {
                num_of_semicolons++;
        }

        //running each of the semicolon commands
        for(int i=0;i<num_of_semicolons;i++)
        {
            char *token[1000];
            char *rest = tkn_array[i];
            int arg_no=0;

            //piping and redirection
            if(check(tkn_array[i],'p'))
            {
                pipe_function(tkn_array[i]);
                continue;
            }
            int r = check(tkn_array[i],'r');
            if(r==2 || r==3)
            {
                redirect(tkn_array[i],(r-2));
                continue;
            }
            while(token[arg_no]=strtok_r(rest," \t\n\r",&rest))
            {
                //    printf(" %s",token[i]);
                 arg_no++;
            }

            //executing each command
            if(strcmp(token[0],"cd")==0)
            {
                cd(token,arg_no);
            }
            else if(strcmp(token[0],"pwd")==0)
            {
                pwd();
            }
            else if(strcmp(token[0],"echo")==0)
            {
                echo(token,arg_no);
            }
            else if(strcmp(token[0],"ls")==0)
            {
                ls(token,arg_no);
            }
            else if(strcmp(token[0],"pinfo")==0)
            {
                pinfo(token,arg_no);
            }

            else if(strcmp(token[0],"setenv")==0)
            {
                env(token,arg_no);
            }
            else if(strcmp(token[0],"unsetenv")==0)
            {
                unset(token,arg_no);
            }
            else if(strcmp(token[arg_no-1],"&")==0)
            {
                 background(token);
            }
            else if(strcmp(token[0],"exit")==0)
            {
                exit(0);
            }
            else if(strcmp(token[0],"quit")==0)
            {

                 exit(0);
            }
             else if(strcmp(token[0],"bg")==0)
            {
                bg(token,arg_no);
            }
            else if(strcmp(token[0],"fg")==0)
            {
                fg(token,arg_no);
            }
            else if(strcmp(token[0],"kjob")==0)
            {
                kjob(token,arg_no);
            }
            else if(strcmp(token[0],"jobs")==0)
            {
                job_print();
             }
             else if(strcmp(token[0],"overkill")==0)
             {
               overkill();
             }
            else
            {
                 foreground(token);
            }


        }
        print_pmt(username,sysname);
    }
    return 0;
}
