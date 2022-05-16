#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"

// Job initialization
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
    job->acquired_time=0;
    job->total_time=0;
    job->num_requests=0;
    job->pending_request=0; 
    return job;
}

// Deallocates memory for job
void destroyJob(Job *job){
    free(job);
}

// Request initialization
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

// Deallocates memory for request
void destroyRequest(Request *req){
    free(req);
}

// Release initialization
Release * createRelease(char str[]){
    Release *release = malloc(sizeof(Release));
    char *token=strtok(str," ");
    release->release_time=atoi(token);
    token=strtok(NULL," ");
    release->job_num=atoi(token+2);
    token=strtok(NULL," ");
    release->num_devices=atoi(token+2);
    return release;
}

// Deallocates memory for release
void destroyRelease(Release *rel){
    free(rel);
}

// Deallocates memory for node
void destroyNode(Node *node){
    free(node);
}