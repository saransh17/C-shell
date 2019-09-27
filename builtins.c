#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "funcs.h"

int call_pwd(char *org_path,int x)
{
	char mod_path[PATH_MAX];
	getcwd(mod_path,PATH_MAX);
	if(x==0)
	{
		printf("%s\n",mod_path);
	}
	else
	{
		char *p=strstr(mod_path,org_path);
		if(!p)
		{
			printf("%s\n",mod_path);
		}
		else
		{
			printf("~%s\n",&mod_path[strlen(org_path)]);

		}
	}
	return 1;
}	

int call_echo(char **args)
{	
	for(int i=1;args[i]!=NULL;i++)
	{
		printf("%s ",args[i]);
	}
	printf("\n");
	return 1;
}
int call_cd(char *location,char *my_path)
{

	if(location==NULL||strcmp(location,"~")==0)
	{
		chdir(my_path);
	}	
	else
	{
		chdir(location);
	}
	return 1;
}