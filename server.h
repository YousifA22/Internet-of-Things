#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SENSOR "/tmp/my_se"
#define ACUATOR "/tmp/my_ac"

#define CLOUD_FIFO "/tmp/my_cloud"


struct data_to_pass_st {
    pid_t  device_pid;
    char name[2000];
    
    int off;
    int value;
 
    
    
};
