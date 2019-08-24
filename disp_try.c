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

const int l_siz=1e4;
const int r_siz=1e6;
/*char **stplit_commands(char* command,char *)
{
	char del[]=";";
}*/


int main()
{
	int len;
	char *user_name,*comp;
	user_name=getlogin();
	
	char host_name[l_siz];host_name[l_siz-1]='\0';
	gethostname(host_name,l_siz-1);

	char path[PATH_MAX];
	getcwd(path,sizeof(path));
	len=strlen(path);
	//printf("<%s@%s:%s>\n",user_name,host_name,path);
	while(1)
	{
		char n_path[PATH_MAX];
		getcwd(n_path,PATH_MAX);
		char *p=strstr(n_path,path);
		if(!p)
		{
			printf("<%s@%s:%s> ",user_name,host_name,n_path);
		}
		else
		{
			if(!strcmp(path,n_path))			
				printf("<%s@%s:~%s> ",user_name,host_name,&n_path[strlen(path)]);
			else
				printf("<%s@%s:~%s> ",user_name,host_name,&n_path[strlen(path)]);
		}
		ssize_t buffer=0;
		char *command=NULL,delim[]=" \n";
		getline(&command,&buffer,stdin);
		char **args;
		args=(char**)malloc(sizeof(char**)*1000);
        int arg_p=0;
        char *tokens=strtok(command,delim);
        while(tokens!=NULL)
        {
            args[arg_p]=(char*)malloc(sizeof(char)*10000);
            strcpy(args[arg_p],tokens);
            tokens= strtok(NULL," \n\t\r");
            arg_p++;
            //printf("%s\n", argv[i]);
       	}
       	int ret;
       	if(args[0]==0)
       	{
       		continue;
       	}
       	else if(strcmp(args[0],"cd")==0)
       	{
       		call_cd(args[1],path);
       	}
       	else if(strcmp(args[0],"echo")==0)
       	{
       		ret=call_echo(args);
       	}
       	else if(strcmp(args[0],"pwd")==0)
       	{
       		if(arg_p==1)
       			ret=call_pwd(path,0);
       		else
       			{
       				if(!strcmp(args[1],"-r"))
       					ret=call_pwd(path,1);
       				else
       					ret=call_pwd(path,0);
       			}
       	}
       	else if(strcmp(args[0],"ls")==0)
       	{
       		if(arg_p==1)
       			ret=call_ls_a(args,arg_p,n_path,0);
       		else if(arg_p==2)
       		{
       			if(!strcmp(args[1],"-a"))
       				ret=call_ls_a(args,arg_p,n_path,1);
       			else if(!strcmp(args[1],"-l"))
       				ret =call_lsl_a(args,arg_p,n_path,0);
       			else if(strcmp(args[1],"-al")==0||strcmp(args[1],"-la")==0)
       				ret=call_lsl_a(args,arg_p,n_path,1);
       			else 
                              {
                                    if(strcmp(args[1],"~")==0)
                                          ret=call_lsdir(args,arg_p,path,1);
                                    else
                                          ret=call_lsdir(args,arg_p,path,0);  
                              }
       		}
       		else if(arg_p==3)
       		{
       			if((strcmp(args[1],"-l")==0&&strcmp(args[2],"-a")==0)||(strcmp(args[2],"-l")==0&&strcmp(args[1],"-a")==0))
       				ret=call_lsl_a(args,arg_p,n_path,1);
       		}
       		else
       		{
       			printf("Invalid !\n");
       		}
       	}
       	else
            {
                  int xi=call_ground(args,arg_p);
            }
	}
	return 0;
}