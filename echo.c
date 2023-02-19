#include"headers.h"

void echo(char* token[],int arg_no)
{
    char output_str[10000];
    if(arg_no < 2)
    {
        printf("pls provide input to echo\n");
        return;
    }
    strcpy(output_str,token[1]);
    strcat(output_str," ");
    for(int w = 2;w <arg_no ;w++)
    {
        strcat(output_str,token[w]);
        strcat(output_str," ");
    }
    int len = strlen(output_str);
    if(output_str[0]=='"' && output_str[len -2] == '"')
    {
        output_str[len-2]='\0';
        printf("%s\n",&output_str[1]);
    }
    else
    {
        printf("%s\n",output_str);
    }
    return;
 
}