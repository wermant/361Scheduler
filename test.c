#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void main(){
    char str[]="5 M=60 S=10 Q=5";
    System *test=createSystem(str);
    printf("%d\n%d\n%d\n%d\n",test->start_time,test->main_memory,test->serial_devices,test->quantum);    
}