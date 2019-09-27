#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "funcs.h"
int call_setenv(char **args,int it_arg)
{
    if(it_arg>=4)
    {
      printf("Invalid input\n");
      printf("Arguments more than expected <usage: setenv variable [newvalue]>\n");
    }
    if(it_arg<=1)
    {
      printf("Invalid input\n");
      printf("Arguments less than expected <usage: setenv variable [newvalue]>\n");
    }
  else
  {
    if(it_arg==3)
    {
      int key=setenv(args[1],args[2],1);
      if(key!=0)
      {
        printf("Error setting environment variable\n");
        perror("setenv");
      }
    }
    else if(it_arg==2)
    {
      int key=setenv(args[1],"",1);
      if(key!=0)
      {
        printf("Error setting env var\n");
        perror("setenv");
      }
    }
    
  }
  return 1;
}
int call_unsetenv(char **args,int it_arg)
{
  if(it_arg>=3)
    {
      printf("Invalid input\n");
      printf("Arguments more than expected <usage: unsetenv variable>\n");
    }
    if(it_arg<=1)
    {
      printf("Invalid input\n");
      printf("Arguments less than expected <usage: unsetenv variable>\n");
    }
  else
  {
    int key=unsetenv(args[1]);
    if(key==-1)
    {
      printf("Error unsetting env var\n");
      perror("unsetenv");
    }
  }
  return 1;
}