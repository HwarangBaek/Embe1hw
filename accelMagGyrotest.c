#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main (void)
{
    while(1){
    //Accel();
    //Mag();
    Gyro();
    sleep(0.1);
    }
    return 0;
}
