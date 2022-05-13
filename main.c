#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structures.h"
#include "queues.h"
#include "display.h"

int start_time;
int main_memory;
int remaining_memory;
int devices;
int remaining_devices;
int quantum;
int run_count=0;
int ready_queue_count = 0;
int *time_arr;

Node *running_job;
Node *headh1;
Node *headh2;
Node *headwait;
Node *headready;
Node *headfinish;

int isSafe(Node* head){
    int work = remaining_devices; 
    int finish[ready_queue_count];
    for(int i = 0; i < ready_queue_count; i++){
        finish[i] = 0; 
    }
    Node* temp = head; 
    int exit_counter = 0;
    while(exit_counter < ready_queue_count) {
        int found = 0; 
        for(int i = 0; i < ready_queue_count; i++){
            if(finish[i] == 0) {
                int j = 0; 
                /*for(int j = 0; j < ready_queue_count; j++){
                    if((temp->job->num_devices - temp->job->used_devices) > work) {
                        break;
                    }
                    temp = temp->next;  
                }*/
                if(temp->job->num_devices - temp->job->used_devices > work){
                    break;
                }
                else {
                    work += temp->job->used_devices;
                    exit_counter++; 
                    finish[i] = 1;
                    found = 1; 
                }
            }
        }
        if(found == 0){
            return 0;
        }
    }
    return 1; 
}

int grantRequest(Request* req, Node* running_job){
    int need = running_job->job->num_devices - running_job->job->used_devices; 
    int safe = 0;
    if(req->num_devices <= need && req->num_devices <= remaining_devices){
        remaining_devices -= req->num_devices;  //Subtract available devices
        running_job->job->used_devices += req->num_devices; //Allocate resources to job
        safe = isSafe(running_job);  //Check if the new state is safe
        if(safe == 0) {  //Restore the old state if it was unsafe
            remaining_devices += req->num_devices;
            running_job->job->used_devices -= req->num_devices;
        }
    }
    return safe; 
}

void main(int argc, char *argv[]){
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
    time_arr=malloc(100*sizeof(int));
    int index=1;
    fp=fopen(argv[1],"r");
    for (int i=0;i<100;i++){
        time_arr[i]=0;
    }
    while (read=getline(&line,&len,fp)!=-1){
        int time=atoi(line+2);
        if (time!=9999){
            time_arr[time]=1;
            index=time;
        }
        else{
            time_arr[index+1]=9999;
            time_arr[index+2]=-1;
            index=1;
        }
    }
    fclose(fp);
    fp=fopen(argv[1],"r");
    line=NULL;
    len=0;
    while (time_arr[index]!=-1){
        if (time_arr[index]==0){
            if (running_job!=NULL){
                if (running_job->job->acquired_time==running_job->job->run_time){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    finish_push(headfinish,temp);
                    remaining_devices+=temp->job->used_devices;
                    remaining_memory+=temp->job->needed_memory;
                    running_job=headready;
                    run_count=0;
                }  
                else if (run_count==quantum && running_job!=NULL){
                    run_count=0;
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
            }
            Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
            if (temp_node!=NULL){
                remaining_devices-=temp_node->job->used_devices;
                remaining_memory-=temp_node->job->needed_memory;
                ready_queue_count++; //Increase rqc when adding to rq
            }
            if (headready->job!=NULL && running_job==NULL){
                running_job = headready;
            }
            updateTime(headh1,headh2,headwait,headready->next);
            if (running_job!=NULL){
                running_job->job->acquired_time++;
                running_job->job->total_time++;
            }
            if (run_count!=quantum){
                run_count++;
            }
            else{
                run_count=0;
            }
        }
        else if(time_arr[index]==9999){
            while (running_job!=NULL){
                if (running_job->job->acquired_time==running_job->job->run_time){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    finish_push(headfinish,temp);
                    remaining_devices+=temp->job->used_devices;
                    remaining_memory+=temp->job->needed_memory;
                    run_count=0;
                }  
                else if (run_count==quantum && running_job!=NULL){
                    run_count=0;
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
                Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
                if (temp_node!=NULL){
                    remaining_devices-=temp_node->job->used_devices;
                    remaining_memory-=temp_node->job->needed_memory;
                    ready_queue_count++; //Increase rqc when adding to rq
                }
                if (headready->job!=NULL && running_job==NULL){
                    running_job = headready;
                }
                updateTime(headh1,headh2,headwait,headready->next);
                /*printf("Ready Queue\n");
                display(headready);
                printf("Waiting Queue\n");
                display(headwait);
                printf("Finished\n");
                display(headfinish);*/
                if (running_job!=NULL){
                    running_job->job->acquired_time++;
                    running_job->job->total_time++;
                }
                if (run_count!=quantum){
                    run_count++;
                }
                else{
                    run_count=0;
                }
            }
            printf("Ready Queue\n");
            display(headready);
            printf("Waiting Queue\n");
            display(headwait);
            printf("Finished\n");
            display(headfinish);
        }
        else{
            getline(&line,&len,fp);
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
            else if (strcmp(token,"A")==0){
                Job *new_job=createJob(line+2);
                if (new_job->priority==1){
                    hq1_push(headh1,new_job,main_memory,devices);
                }
                else{
                    hq2_push(headh2,new_job,main_memory,devices);
                }
            }
            else if (strcmp(token,"Q")==0){
                Request *req = createRequest(line+2);
                //Banker's algorithm to decide whether to grant request
                if (req->job_num==running_job->job->job_num){
                    running_job->job->num_requests++;
                    if(grantRequest(req, running_job) == 1){
                    }
                    else {
                        Node *temp=pop(headready);
                        wait_push(headwait,temp);
                        running_job=headready;
                    }
                }
            }
            else if (strcmp(token,"D")==0){
                /*printf("Ready Queue\n");
                display(headready);
                printf("Waiting Queue\n");
                display(headwait);
                printf("Finished\n");*/
            
            }
            Node *temp_node=ready_push(headh1,headh2,headwait,headready,remaining_memory,remaining_devices);
            if (temp_node!=NULL){
                remaining_devices-=temp_node->job->used_devices;
                remaining_memory-=temp_node->job->needed_memory;
                ready_queue_count++; //Increase rqc when adding to rq
            }
            if (running_job!=NULL){
                if (running_job->job->acquired_time==running_job->job->run_time){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    finish_push(headfinish,temp);
                    remaining_devices+=temp->job->used_devices;
                    remaining_memory+=temp->job->needed_memory;
                    running_job=headready;
                    run_count=0;
                }  
                else if (run_count==quantum){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
            }
           
            if (headready->job!=NULL && running_job==NULL){
                running_job = headready;
            }
            /*printf("Ready Queue\n");
            display(headready);
            printf("Waiting Queue\n");
            display(headwait);
            printf("Finished\n");
            display(headfinish);*/
            updateTime(headh1,headh2,headwait,headready->next);
            if (running_job!=NULL){
                running_job->job->acquired_time++;
                running_job->job->total_time++;
            }
            if (run_count!=quantum){
                run_count++;
            }
            else{
                run_count=0;
            }
        }
        index++;
    }
}
