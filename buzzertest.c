#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h> 
#include <sys/msg.h>
#include "buzzer.h"
int main(void){
	buzzerInit();
	buzzerPlaySong(3);
	printf("FREQUENCY 3 playing \r\n");
	sleep(3);
	buzzerPlaySong(6);
	
	printf("FREQUENCY 6 playing \r\n");
	sleep(2);
	buzzerStopSong();

	}
