#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structures.h"
#include "hold_queue1.h"
#include "hold_queue2.h"
#include "ready_queue.h"
#include "wait_queue.h"

int start_time;
int main_memory;
int remaining_memory;
int devices;
int remaining_devices;
int quantum;

Node *running_job;
Node *headh1;
Node *headh2;
Node *headwait;
Node *headready;

int main(int argc, char *argv[]){
    assert(argc==2);
    FILE *fp;
    char *line=NULL;
    size_t len=0;
    ssize_t read;
    char *token;
    fp=fopen(argv[1],"r");
    while (getline(&line,&len,fp)!=-1){
        token=strtok(line," ");
        if (strcmp(token,"C")==0){
            token=strtok(NULL," ");
            start_time=atoi(token);
            token = strtok(NULL, " ");
            main_memory=atoi(token+2);
            remaining_memory=main_memory;
            token=strtok(NULL," ");
            devices=atoi(token+2);
            remaining_devices=devices;
            token=strtok(NULL, " ");
            quantum=atoi(token+2);
            printf("%d %d %d",main_memory,devices,quantum);
        }
    }
}
