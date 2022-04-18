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

Job * createJob(char str[]){
    Job *job = malloc(sizeof(Job));
    char *token=strtok(str," ");
    job->arrival=atoi(token);
    token=strtok(NULL," ");
    job->job_num=atoi(token+2);
    token=strtok(NULL," ");
    job->needed_memory=atoi(token+2);
    token=strtok(NULL," ");
    job->num_devices = atoi(token+2);
    token=strtok(NULL," ");
    job->run_time = atoi(token+2);
    token=strtok(NULL," ");
    job->priority = atoi(token+2);
    return job;
}

typedef struct Request{
    int arrival;
    int job_num;
    int num_devices;
}Request;

Request * createRequest(char str[]){
    Request *req = malloc(sizeof(Request));
    char *token=strtok(str," ");
    req->arrival=atoi(token);
    token=strtok(NULL," ");
    req->job_num=atoi(token+2);
    token=strtok(NULL," ");
    req->num_devices=atoi(token+2);
    return req;
}

typedef struct Release{
    int release_time;
    int job_num;
    int num_devices;
}Release;

Release * createRelease(char str[]){
    Release *release = malloc(sizeof(Release));
    char *token=strtok(str," ");
    release->release_time=atoi(token);
    token=strtok(NULL," ");
    release->job_num=atoi(token+2);
    token=strtok(NULL," ");
    release->num_devices=atoi(token+2);
    return req;
}