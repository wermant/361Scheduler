#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"

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

typedef struct Job{
    int arrival;
    int job_num;
    int needed_memory;
    int num_devices;
    int run_time;
    int priority;
}Job;

typedef struct Request{
    int arrival;
    int job_num;
    int num_devices;
}Request;

typedef struct Release{
    int release_time;
    int job_num;
    int num_devices;
}Release;
