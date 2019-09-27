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

int call_pinfo(char **args)
{
    //printf("reached\n");
    int pid;
    char *str2 = malloc(PATH_MAX);
    
    if(args[1]!=0)
    {
        strcpy(str2,args[1]);
        printf("pid -- %s\n", args[1]);
    }    
    else 
    {
        pid = getpid();
        printf("pid -- %d\n",pid);
        sprintf(str2,"%d",pid);
    }
    char str1d[1000],str1[1000];
    strcpy(str1,"/proc/");
    strcpy(str1d,str1);
    
    char str4[1000];
    char str3[1000];
    strcpy(str3,"/exe");
    strcpy(str4,"/stat");
    char str2d[1000];
    strcpy(str2d, str2);
    strcat(str2d, str4);
    strcat(str1,str2d);
    
    FILE *file=fopen(str1,"r");
    if(file==NULL)
    {
        perror("No such process");
        return -1;
    }   
    int i=0,j=0;
    char info[100][100];
    char ans[1000][1000];
    while(i<23)
    {
        if(i!=2&&i!=22)
        {
            fscanf(file,"%s", info[i++]);
        }
        else
        {
            fscanf(file, "%s", ans[j++]);
            i++;
        }

    }   
    printf("Process Status -- %s\nmemory -- %s\n",ans[0],ans[1]);
    fclose(file);
    strcat(str2,str3);
    strcat(str1d,str2);
    printf("%s\n", str1d);
    char *buf;
    buf=(char*)malloc(PATH_MAX);
    int check=readlink(str1d,buf,PATH_MAX);
    if(check==0)
        {
            perror("PID not found\n");
            return -1;
        }
    else    
        printf("Executable Path -- %s\n",buf);
    
        
    //printf("reached\n");
    return 1;
}
