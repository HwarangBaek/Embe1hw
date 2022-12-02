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
#include <dirent.h>
#include "textlcd.h"

int main(int argc, char **argv){

	int lineFlag;
	const char *string1;
	const char *string2;
	lineFlag = strtol(argv[1],NULL,10);
	if (lineFlag == 1){
		string1 = argv[2];
		string2 = NULL;
	
	
	}
	else if (lineFlag == 2){
	
	string2 = argv[2];
	string1 = NULL;
	
	
	}
	else{
	
		printf("lineFlag : %d wrong . range (1 ~ 2)\n", lineFlag);
		return 1;
	
	}
lcdtextWrite(string1, string2, lineFlag);
return 0;


}
