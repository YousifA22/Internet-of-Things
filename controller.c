#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include "server.h"
#include <ctype.h>
#include <signal.h> 




	
int count=0;
int flag=0;


void handle_usr1(int sig){

	flag=1;
	printf("Threshold reached, Sending OFF signal to cloud!");
	
}
void handle_usr2(int sig){

	flag=0;
	printf("Threshold not reached, Sending ON signal to cloud!");
	
	
}

int main(){

	struct sigaction act;
	struct sigaction act2;
	
	act.sa_flags=0;
	act.sa_handler=&handle_usr1;
	
	act2.sa_flags=0;
	act2.sa_handler=&handle_usr2;
	
	struct data_to_pass_st my_data;
	
	int threshold=5;
	

	mkfifo(ACUATOR, 0777);
	mkfifo(CLOUD_FIFO, 0777);
	int sensor,acuator,cloud;
   
	sensor = open(SENSOR, O_RDONLY);


	
	

	pid_t pid;
	
	
	
	
	
	
	pid=fork();
	
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);

		case 0:
			
			while(1){
			if (read(sensor, &my_data, sizeof(my_data)) == -1){
			
				return 2;
				}
				
				
				printf("RECIEVED : %d\n from %d PID,  device name = %s, threshold %d \n",my_data.value,my_data.device_pid,my_data.name,threshold);
				//if(my_data.value<count){
					//for some reason this does not work
					//this would check if my_data stops updating and that it has not reached the threshold
					//kill(getppid(),SIGUSR2);
					//exit(0);
					//}
				
				
				
				if(my_data.value==threshold){
				
					acuator = open(ACUATOR, O_WRONLY);
					if (write(acuator, &my_data,sizeof(my_data)) == -1){
			return 2;
			}
				kill(getppid(),SIGUSR1);
				break;
				}count++;
			
			
			
				
				}
				
		default:
		
			
			sigaction(SIGUSR1,&act,0);
			sigaction(SIGUSR2,&act2,0);
			pause();
			
			if(flag){
			cloud = open(CLOUD_FIFO, O_WRONLY);
			if (write(cloud, &my_data,sizeof(my_data)) == -1){
			return 2;
			}
			}if(!flag){
			cloud = open(CLOUD_FIFO, O_WRONLY);
			my_data.off=1;
			if (write(cloud, &my_data,sizeof(my_data)) == -1){
			return 2;
			}
			}
			
		
			
			exit(0);
			}
			


		
	
		
		
		close(sensor);
		close(acuator);
		close(cloud);
	
		
		
	exit(EXIT_SUCCESS);
}
