#include"headers.h"

void pwd()
{
    char present_dir[1000];
    getcwd(present_dir,sizeof(present_dir));
    printf("%s\n",present_dir);
   
}