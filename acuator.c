#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include "server.h"

int main(){

	int fd;
	
	struct data_to_pass_st my_data;

	
	
		
	
	fd = open(ACUATOR, O_RDONLY);

	
	while(1){
	
 	if (read(fd,&my_data,sizeof(my_data)) != -1){
 		printf("Threshold reached of device with properities : \nPID : %d\nname : %s\n ",my_data.device_pid,my_data.name);
 		
		}break;}
			
		
			
	
	
	
		
		
		
	
		

	close(fd);

		
		
	exit(EXIT_SUCCESS);
	}
