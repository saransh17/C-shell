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
		char *command_line;
		getline(&command_line,&buffer,stdin);
            
      //      char 
            char **comms;
            comms=(char **)malloc(sizeof(char**)*1000);
            
            int comm_p=0;
            char *comm_tok=strtok(command_line,";");
           // printf("%s\n",command_line);

      while(comm_tok!=NULL)
      {
            comms[comm_p]=(char*)malloc(sizeof(char)*1000);
            strcpy(comms[comm_p],comm_tok);
            comm_tok=strtok(NULL,";");
            comm_p++;
      }
     
      //for(int i =0; i<comm_p; i++)
        //    printf("%s\n", comms[i]);
      int it_c=0;
      while(it_c<comm_p)
      {
            char *command=NULL,delim[]=" \n";
            command=(char*)malloc(sizeof(char*)*1000);
            char **args;
            
            strcpy(command,comms[it_c++]);
             
		args=(char**)malloc(sizeof(char**)*1000);
            int arg_p=0;
             
            char *tokens=strtok(command,delim);
            
            while(tokens!=NULL)
            {
            args[arg_p]=(char*)malloc(sizeof(char)*10000);
            strcpy(args[arg_p],tokens);

            tokens= strtok(NULL," \n\t\r\a");
            arg_p++;
            //printf("jtsdfkjhvn");
       	}
       	int ret;
            int checkk=0;
            char str1[1]="<";
            char str2[1]=">";
            char str3[2]=">>";
            int l=0,r=0,sin,sout;
            sin=dup(0);sout=dup(1);
            for(int i=0;i<arg_p;i++)
            {
                  if(strncmp(args[i],str1,1)==0)
                        l=1;
                  if(strncmp(args[i],str2,1)==0)
                        r=1; 
                  if(strncmp(args[i],str3,2)==0)
                        r=2;     
            }
            if(l+r>0)
                  ret=call_red(args,arg_p,l,r);
            if(r>0)
            {
                  args[arg_p-1]=NULL;arg_p--;
                  args[arg_p-1]=NULL;arg_p--;
            }
            if(l>0)
            {
                  char *args1[1000];
                  int i=0;
                  while(strcmp(args[i],str1)!=0)
                  {
                        args1[i]=args[i];
                        i++;
                  }
                  for(i=i;i<arg_p;i++)
                  {
                        args1[i]=args[i+2];
                  }
                  arg_p-=2;
                  for(i=0;i<arg_p;i++)
                  {
                        args[i]=args1[i];
                  }
                  args[arg_p]=NULL;
            }
      
            if(strcmp(args[0],"quit")==0)
            {
                  printf("Exiting shell\n----------------------------------\nRoll no:2018114016\n----------------------------------\n");
                  exit(0);
            }
       	else if(strcmp(args[0],"cd")==0)
       	{
       		call_cd(args[1],path);
       	}
       	else if(strcmp(args[0],"echo")==0)
       	{
       		ret=call_echo(args);
       	}
            else if(strcmp(args[0],"setenv")==0)
            {
                  int it_args=0;
                  while(args[it_args]!=NULL)
                        it_args++;
                  ret=call_setenv(args,it_args);
            }
            else if(strcmp(args[0],"unsetenv")==0)
            {
                  int it_args=0;
                  while(args[it_args]!=NULL)
                        it_args++;
                  ret=call_unsetenv(args,it_args);
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
            else if(strcmp(args[0],"pinfo")==0)
            {
                  int ret=call_pinfo(args);
            }
       	else
            {
                  int xi=call_ground(args,arg_p);
            }
            if(args[0]==0)
            {
                  continue;
            }
            dup2(sin,0);
            dup2(sout,1);

      }
      
	}
	return 0;
}