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
Node *headfinish;

int main(int argc, char *argv[]){
    assert(argc==2);
    running_job=NULL;
    headh1=init();
    headh2=init();
    headwait=init();
    headready=init();
    headfinish=init();
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
        if (strcmp(token,"D")==0){
            token=strtok(NULL," ");
            if (strcmp(token,"9999")==0){
                while (running_job!=NULL){
                    if (running_job->job->acquired_time==running_job->job->run_time){
                        finish_push(headfinish,running_job);
                        remaining_devices+=running_job->job->used_devices;
                        remaining_memory+=running_job->job->needed_memory;
                        running_job=NULL;
                        run_count=0;
                    }
                    else if (run_count==quantum && running_job!=NULL){
                        wait_push(headwait,running_job);
                        remaining_devices+=running_job->job->used_devices;
                        remaining_memory+=running_job->job->needed_memory;
                        running_job=NULL;
                        run_count=0;
                    }   
                    Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
                    if (temp_node!=NULL){
                        remaining_devices-=temp_node->job->used_devices;
                        remaining_memory-=temp_node->job->needed_memory;
                    }
                    if (run_count==0&&headready->job!=NULL){
                        running_job=pop(headready);
                    }
                    printf("Ready Queue\n");
                    display(headready);
                    printf("Waiting Queue\n");
                    display(headwait);
                    printf("Finished\n");
                    display(headfinish);
                    updateTime(headh1,headh2,headwait,headready);
                    if (running_job!=NULL){
                        running_job->job->acquired_time++;
                        running_job->job->total_time++;
                        run_count++; 
                    }
                }
                return;
            }
            else{
                printf("Waiting Queue\n");
                display(headwait);
                printf("Ready Queue\n");
                display(headready);
                printf("Finished\n");
                display(headfinish);
            }
        }
        if (running_job!=NULL){
            if (running_job->job->acquired_time==running_job->job->run_time){
                finish_push(headfinish,running_job);
                remaining_devices+=running_job->job->used_devices;
                remaining_memory+=running_job->job->needed_memory;
                running_job=NULL;
                run_count=0;
            }  
            else if (run_count==quantum && running_job!=NULL){
                wait_push(headwait,running_job);
                remaining_devices+=running_job->job->used_devices;
                remaining_memory+=running_job->job->needed_memory;
                running_job=NULL;
                run_count=0;
            }
        }
        Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
        if (temp_node!=NULL){
            remaining_devices-=temp_node->job->used_devices;
            remaining_memory-=temp_node->job->needed_memory;
        }
        if (run_count==0&&headready->job!=NULL){
            running_job=pop(headready);
        }
        
        updateTime(headh1,headh2,headwait,headready);
        if (running_job!=NULL){
            running_job->job->acquired_time++;
            running_job->job->total_time++;
            run_count++; 
        }
    }
}
