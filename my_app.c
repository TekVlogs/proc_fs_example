#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>


#define WR_FLAG _IOW('a','a',int32_t*)
#define RD_FLAG _IOR('a','b',int32_t*)

struct my_arr {
    int arr;
    int dd;
};


void main()
{
    struct my_arr data[5], value[5];
    printf("main function..\n");
    printf("init ..\n");
    for(int i=0 ; i< 5; i++)
    {
        data[i].arr = i*i;
        data[i].dd = i*i; 
    }
    
    int fd;
    fd = open("/proc/ov426", O_RDWR);

    ioctl(fd , WR_FLAG, (struct my_arr*) data);
    ioctl(fd, RD_FLAG, (struct my_arr *) value);
    
    for(int i=0 ; i< 5; i++)
    {
        printf("value : %d  , %d \n", value[i].arr, value[i].dd);
    }

    
}

