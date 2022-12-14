#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"

int main(void){
	ledLibInit();
	ledOnOff(0,1);
	sleep(1);
   ledOnOff(0,0); ledOnOff(1,1);
	sleep(1);
    ledOnOff(1,0); ledOnOff(2,1);
	sleep(1);
	ledOnOff(3,1);
	ledStatus();
	ledLibExit();		
	}
