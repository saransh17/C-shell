#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/utsname.h>
#include "funcs.h"

int call_ground(char **args,int arg_p)
{
    int ret;
    if(strcmp(args[arg_p-1],"&")!=0)
        ret=call_fg(args,arg_p);
    else
        ret=call_bg(args,arg_p);
    return ret;
}

int call_fg(char **args,int arg_p)
{
        pid_t pid;
        char *com=args[0];
        pid=fork();
        
        if(pid==0)
        {
            int error=0;//error=-1 fault
            error=execvp(com,args);
            if(error<0)
            {
                perror("Invalid command");
                return 0;
            }
        }
        else if(pid<0)
        {
            perror("Unable to fork");
            return 0;
        }
        else
        {
            int status;
            waitpid(pid,&status,0); 
        }

    return 1;   
}
int call_bg(char **args,int arg_p)
{
        pid_t pid1,pid2;
        int status;
        char *com=args[0];args[arg_p-1]='\0';
        pid1=fork();
        if(pid1==0)
        {
            pid2=fork();
            if(pid2==0)
            {
                int error=0;
                error=execvp(com,args);
                if(error<0)
                {
                    perror("Unable to run command");
                    return 0;
                }
            }
            else if(pid2<0)
            {
                perror("Unable to fork");
                return 0;
            }
            else
            {
                waitpid(pid2,&status,0); 
                if(!status)
                {
                    printf("\n%s with pid %d exited\n",com,pid2);
                }
            }
        }
        else if(pid1<0)
        {
            perror("Unable to fork");
            return 0;
        }  
        return 1;
}   
    
