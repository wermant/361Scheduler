#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

typedef struct System{
    int start_time;
    int main_memory;
    int serial_devices;
    int quantum;
}System;

typedef struct Job{
    int arrival;
    int job_num;
    int needed_memory;
    int num_devices;
    int run_time;
    int priority;
}Job;

typedef struct Request{
    
}Request;