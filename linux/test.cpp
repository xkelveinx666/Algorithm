
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
  
#define MAX_SIZE (PATH_MAX+1)
   
int main()
{
    char current_absolute_path[MAX_SIZE];
    //获取当前目录绝对路径
    if (NULL == realpath("./", current_absolute_path))
    {
        printf("***Error***");
        exit(-1);
    }
    strcat(current_absolute_path, "/");
    printf("current absolute path:%s\n", current_absolute_path);
      
    exit(0);
}