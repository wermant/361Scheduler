#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct System{
    int start_time;
    int main_memory;
    int serial_devices;
    int quantum;
}System;

System * createSystem(char str[]){
    System *sys = malloc(sizeof(System));
    char *token=strtok(str," ");
    sys->start_time=atoi(token);
    token=strtok(NULL," ");
    sys->main_memory=atoi(token+2);
    token=strtok(NULL," ");
    sys->serial_devices=atoi(token+2);
    token=strtok(NULL," ");
    sys->quantum = atoi(token+2);
    return sys;
}

void main(){
    char str[]="5 M=60 S=10 Q=5";
    System *test=createSystem(str);
    printf("%d\n%d\n%d\n%d\n",test->start_time,test->main_memory,test->serial_devices,test->quantum);    
}