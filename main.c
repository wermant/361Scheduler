#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structures.h"
/*#include "hold_queue1.h"
#include "hold_queue2.h"
#include "ready_queue.h"
#include "wait_queue.h"*/
#include "queues.h"
#include "display.h"

int start_time;
int main_memory;
int remaining_memory;
int devices;
int remaining_devices;
int quantum;
int run_count=0;

Node *running_job;
Node *headh1;
Node *headh2;
Node *headwait;
Node *headready;

int main(int argc, char *argv[]){
    assert(argc==2);
    running_job=NULL;
    headh1=init();
    headh2=init();
    headwait=init();
    headready=init();
    FILE *fp;
    char *line=NULL;
    size_t len=0;
    ssize_t read;
    char *token;
    fp=fopen(argv[1],"r");
    while (read=getline(&line,&len,fp)!=-1){
        char *temp=line;
        token=strtok(temp," ");
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
        }
        if (strcmp(token,"A")==0){
            Job *new_job=createJob(line+2);
            if (new_job->priority==1){
                hq1_push(headh1,new_job,main_memory,devices);
                
            }
            else{
                hq2_push(headh2,new_job,main_memory,devices);
            }
        }
        Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
        if (temp_node!=NULL){
            remaining_devices-=temp_node->job->used_devices;
            remaining_memory-=temp_node->job->needed_memory;
        }
        printf("%d\n",running_job==NULL);
        if (run_count==0&&headready->job!=NULL){
            printf("HELLO\n");
            fflush(stdout);
            running_job=pop(headready);
        }
        updateTime(headh1,headh2,headwait,headready);
        if (running_job!=NULL){
            run_count++; 
        }
    }
    fflush(stdout);
}
