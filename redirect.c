#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "funcs.h"


int call_red(char **args,int arg_p,int l,int r)
{
	char infil[10000],outfil[10000];
	//printf("%d %d\n",l,r);
	int fdin,fdout;	
	int key=0;
	int i,li=0,ri=arg_p,rri=arg_p;
	char s1[1]="<";
	char s2[1]=">";
	char s3[2]=">>";
	for(int i=0;i<arg_p;i++)
	{
		if(strncmp(args[i],s1,1)==0)
		{
			//printf("lfound\n");
			li=i;
		}
		if(strncmp(args[i],s2,1)==0)
		{
			//printf("rfound\n");
			ri=i;
		}
		if(strncmp(args[i],s3,1)==0)
		{
			//printf("rrfound\n");
			rri=i;
		}
	}
	//printf("%d %d %d\n",li,ri,rri);
	if(li!=0) strcpy(infil,args[li+1]);
	if(ri!=arg_p) strcpy(outfil,args[ri+1]);
	//printf("%s\n",infil);
	//printf("%s\n",outfil);
	if(l==1)
	{
		fdin=open(infil,O_RDONLY);
        if(fdin!=-1)
        {
            dup2(fdin,0);
       		close(fdin);
        }
        else
        {
        	perror("No such file or directory");
        	return -1;
        }

	}
	if(r==1)
	{
		fdout=open(outfil, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fdout!=-1)
		{
			dup2(fdout,1);
		}
		else
		{
			perror("No such file or directory");
        	return -1;
		}	
	}
	if(r==2)
	{
		fdout=open(outfil, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(fdout!=-1)
		{
			dup2(fdout,1);
		}
		else
		{
			perror("No such file or directory");
        	return -1;
		}	
	}
	return 0;
}