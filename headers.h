//---------------------------------------------header files--------------------------------------------------------------------------

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include <errno.h>
#include <pwd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<grp.h>
#include<sys/wait.h>
#include <sys/utsname.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
//----------------------------------variable declarations-----------------------------------------------------------------------------

char hdPath[1000];
char pmt[1000];
typedef struct job {
    int pid;
    int is_back;
    char name[1000];
}job;

extern job bjob[1000];
extern job foreground_job;
extern int backgroundJob_count;
extern pid_t shellid;
extern pid_t childpid;


//---------------------------------------------function declarations------------------------------------------------------------------


void cd(char* token[],int arg_no);
void pwd();
void ls(char* token[],int arg_no);
void echo(char* token[],int arg_no);
void background(char* token[]);
void foreground(char* token[]);
void pinfo(char* token[],int arg_no);
void env(char* token[],int arg_no);
void unset(char* token[],int arg_no);
void redirect(char *buf,int x);
void pipe_function(char *buf);
void fg(char *token[],int arg_no);
void bg(char *token[],int arg_no);
void kjob(char* token[],int arg_no);
void job_print();
void overkill();
int check_p(char *str,char c);
