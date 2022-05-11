#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structures.h"
#include "hold_queue1.h"
#include "hold_queue2.h"
#include "ready_queue.h"
#include "wait_queue.h"
#include "display.h"

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
    running_job=malloc(sizeof(Node));
    headh1=malloc(sizeof(Node));
    headh1->job=NULL;
    headh1->next=NULL;
    headh1->prev=NULL;
    headh2=malloc(sizeof(Node));
    headh2->job=NULL;
    headh2->next=NULL;
    headh2->prev=NULL;
    headwait=malloc(sizeof(Node));
    headwait->job=NULL;
    headwait->next=NULL;
    headwait->prev=NULL;
    headready=malloc(sizeof(Node));
    headready->job=NULL;
    headready->next=NULL;
    headready->prev=NULL;
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
            printf("Hold queue 1\n");
            display(headh1);
            fflush(stdout);
            printf("Hold queue 2\n");
            display(headh2);
            ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
            Node *temp=headready;
            while (temp!=NULL){
                remaining_devices-=temp->job->used_devices;
                remaining_memory-=temp->job->needed_memory;
                temp=temp->next;
            }
            printf("Ready Queue\n");
            display(headready);
        }
    }
    fflush(stdout);
    Node *temp=pop(headh1);
    printf("%d %d %d\n",temp->job->job_num,temp->job->arrival,temp->job->priority);
}
