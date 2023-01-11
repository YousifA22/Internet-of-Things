 #include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include "server.h"

int value;

int main(){

	struct data_to_pass_st my_data;
	printf("Enter your sensors name?: ");
	scanf("%s",my_data.name);
	printf("by how much do you want to increase it by?: ");
	scanf("%d",&value);
	
	int fd;
	
	my_data.value=0;
	my_data.device_pid=getpid();
	my_data.off=0;



	

	mkfifo(SENSOR, 0777);
	
	
        
       
  
        
      
        	
	fd = open(SENSOR, O_WRONLY);
	if (fd == -1){
	return 1;
	
	}
	while(1){
	
		printf("Sent:  %d\n", my_data.value);
		if (write(fd, &my_data,sizeof(my_data)) == -1){
		return 2;
		}
		
		sleep(2);
		if (my_data.value==value){
		break;
		}
		my_data.value++;
		
		}
		
	
	
	close(fd);

	exit(EXIT_SUCCESS);
	}
