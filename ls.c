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

void perms(struct stat stats)
{

    printf((S_ISDIR(stats.st_mode)) ? "d" : "-");

    printf((stats.st_mode & S_IRUSR) ? "r" : "-");
    printf((stats.st_mode & S_IWUSR) ? "w" : "-");
    printf((stats.st_mode & S_IXUSR) ? "x" : "-");
    printf((stats.st_mode & S_IRGRP) ? "r" : "-");
    printf((stats.st_mode & S_IWGRP) ? "w" : "-");
    printf((stats.st_mode & S_IXGRP) ? "x" : "-");
    printf((stats.st_mode & S_IROTH) ? "r" : "-");
    printf((stats.st_mode & S_IWOTH) ? "w" : "-");
    printf((stats.st_mode & S_IXOTH) ? "x" : "-");
}

int call_ls_a(char **args,int arg_p,char *path,int x)
{
	int i=0;
	DIR *direc;
	struct dirent *file;
	char mod_path[PATH_MAX];
	getcwd(mod_path,PATH_MAX);
		direc=opendir(mod_path);
		if(direc!=NULL)
		{
			file=readdir(direc);
			
			while(file!=NULL)
			{
					if(x==0)
					{
						if(file->d_name[0]!='.')
						printf("%s \n",file->d_name);
					}
					else
					{
						printf("%s \n",file->d_name);
					}				
					
				file=readdir(direc);
			}
			closedir(direc);
		}
		else
		{
			perror("0");
			return 1 ;
		}
	
	return 1;
}
int call_lsl_a(char **args,int arg_p,char *path,int x)
{
	//printf("%s\n",path);
	int i=0;
	char buffer[10000];
	char mod_path[PATH_MAX];
	getcwd(mod_path,PATH_MAX);
	DIR *direc;
	direc=opendir(mod_path);
	struct dirent *file;
	struct stat stats;
	if(direc!=NULL)
	{
		file=readdir(direc);
		while(file!=NULL)
		{
			if(x==0)
			{	
				if(file->d_name[0]!='.')
				{
						char timebuf[2000];
						strftime(timebuf,2000, "%b %d %H:%M", localtime(&(stats.st_mtime)));
						sprintf(buffer, "%s/%s",path,file->d_name);
                      	lstat(buffer,&stats);              
                        
                        perms(stats);
                        int nl=stats.st_nlink;
                        int ns=stats.st_size;
                        printf(" %d",nl);
                        printf(" %s", getpwuid(stats.st_uid)->pw_name);
                        printf(" %s", getgrgid(stats.st_gid)->gr_name);
                        printf(" %d\t",ns);                
                        printf("%s", timebuf);
                        printf(" %s",file->d_name);
                        printf("\n");
				}
				file=readdir(direc);
			}
			else
			{

						char timebuf[2000];
						strftime(timebuf,2000, "%b %d %H:%M", localtime(&(stats.st_mtime)));
						sprintf(buffer, "%s/%s",path,file->d_name);
                      	lstat(buffer,&stats);              
                        
                        perms(stats);
                        int nl=stats.st_nlink;
                        int ns=stats.st_size;
                        printf(" %d", nl);
                        printf(" %s", getpwuid(stats.st_uid)->pw_name);
                        printf(" %s", getgrgid(stats.st_gid)->gr_name);
                        printf(" %.d\t",ns);
                        printf("%s", timebuf);
                        printf(" %s",file->d_name);
                        printf("\n");
				
						file=readdir(direc);
			}
		}
		closedir(direc);
	}	
	else
	{
		perror("3");
		return 1;
	}
	return 1;
}
int call_lsdir(char **args,int arg_p,char *path,int x)
{
	int i=0;
	DIR *direc;
	struct dirent *file;
	if(x==1)
	{
			direc=opendir(path);
			if(direc!=NULL)
			{
				file=readdir(direc);
				while(file!=NULL)
				{
					printf("%s \n",file->d_name);	
					file=readdir(direc);
				}
				closedir(direc);
			}
			else
			{
				perror("4");
				return 1 ;
			}
	}
	else
	{
		direc=opendir(args[1]);
			if(direc!=NULL)
			{
				file=readdir(direc);
				while(file!=NULL)
				{
					if(file->d_name[0]!='.')
						printf("%s \n",file->d_name);	
					file=readdir(direc);
				}
				closedir(direc);
			}
			else
			{
				perror("4");
				return 1 ;
			}
	}
	
	return 1;
}