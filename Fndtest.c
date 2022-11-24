#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "fnd.h"
#define MODE_STATIC_DIS                0

int main (int argc, char **argv)
{
    int mode;
    int number;

    if (argv[1][0] == 's')
    {
        mode = MODE_STATIC_DIS
        if (argc < 3)
        {
            perror("Args number is less than 3\n")
            return 1;
        }
        number = atoi(argv[2]);

    }
    if (mode == MODE_STATIC_DIS)
    {
        fndDisp(number, o);
    }
    /*else if(mode == MODE_TIME_DIS)
    {
    struct tm *ptmcur;
    time_t tTime;
    if ( -1 == time(&tTime) )
    return -1;
    ptmcur = localtime(&tTime);
    number = ptmcur->tm_hour * 10000;
    number += ptmcur->tm_min *100;
    number += ptmcur->tm_sec;
    fndDisp(number , 0b1010);
}
else if (mode == MODE_COUNT_DIS)
{
    counter = 0;
    while(1)
    {
       if (!fndDisp(counter , 0))
       break;
       counter++;
       sleep(1);
       if (counter > number )
       break;
    }
}*/
return 0;
}