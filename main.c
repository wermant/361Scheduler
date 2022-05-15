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
int if_req=0;

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
                     
                }*/
                if(temp!=NULL&&temp->job->num_devices - temp->job->used_devices > work){
                }
                else if (temp!=NULL&&temp->job->num_devices - temp->job->used_devices < work){
                    work += temp->job->used_devices;
                    exit_counter++; 
                    finish[i] = 1;
                    found = 1; 
                }    
            }
            if (temp->next!=NULL){
                temp = temp->next; 
            }
            else{
                temp=head;
            }
        }
        if(found == 0){
            return 0;
        }
    }
    return 1; 
}

int grantRequest(int requested_devices, Node* running_job){
    int need = running_job->job->num_devices - running_job->job->used_devices; 
    int safe = 0;
    if(requested_devices <= need && requested_devices <= remaining_devices){
        remaining_devices -= requested_devices;  //Subtract available devices
        running_job->job->used_devices += requested_devices; //Allocate resources to job
        safe = isSafe(headready);  //Check if the new state is safe
        if(safe == 0) {  //Restore the old state if it was unsafe
            remaining_devices += requested_devices;
            running_job->job->used_devices -= requested_devices;
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
                }  
                else if (run_count==quantum && running_job!=NULL){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
            }
            //Check wait queue if requests can be granted upon device release
            if(headwait->job != NULL){
                Node *wait_node = headwait;
                while(wait_node != NULL){
                    if(grantRequest(wait_node->job->pending_request, wait_node) == 1){
                        //Push to ready queue if safe, granting request in the process
                        wait_node->job->pending_request = 0;
                        wait_node = wait_node->next; 
                        Node *temp2 = pop(wait_node->prev);
                        push_helper(headready, temp2);
                    }
                    else {
                        wait_node = wait_node->next; 
                    }
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
                run_count=1;
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
                }  
                else if (run_count==quantum && running_job!=NULL){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
                //Check wait queue if requests can be granted upon device release
                if(headwait->job != NULL){
                    Node *wait_node = headwait; 
                    while(wait_node != NULL){
                        if(grantRequest(wait_node->job->pending_request, wait_node) == 1){
                            //Push to ready queue if safe, granting request in the process
                            wait_node->job->pending_request = 0; 
                            wait_node = wait_node->next; 
                            Node *temp2 = pop(wait_node->prev);
                            push_helper(headready, temp2);
                        }
                        else {
                            wait_node = wait_node->next; 
                        }
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
                    run_count=1;
                }
            }
            printf("At time 9999\n");
            printf("Current Available Main Memory: %d\n",remaining_memory);
            printf("Current Devices: %d\n",remaining_devices);
            printf("Completed Jobs:\n");
            finish_display(headfinish);
            printf("Hold Queue 1:\n");
            hold_display(headh1);
            printf("Hold Queue 2:\n");
            hold_display(headh2);
            printf("Ready Queue:\n");
            ready_display(headready);
            printf("Waiting Queue\n");
            ready_display(headwait);
        }
        else {
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
                    if(grantRequest(req->num_devices, running_job) == 0){
                        Node *temp=pop(headready);
                        //Save the request information before sending to wait queue
                        temp->job->pending_request = req->num_devices;
                        wait_push(headwait,temp);
                        running_job=headready;
                    }
                }
                
            }
            else if (strcmp(token,"L")==0){
                Release *rel = createRelease(line+2);
                if (rel->job_num==running_job->job->job_num){
                    running_job->job->used_devices-= rel->num_devices;
                    remaining_devices+=rel->num_devices;
                }
            }
            /*if (strcmp(token,"D")==0){
                printf("At time %s",line+2);
                printf("Current Available Main Memory: %d\n",remaining_memory);
                printf("Current Devices: %d\n",remaining_devices);
                printf("Completed Jobs:\n");
                finish_display(headfinish);
                printf("Hold Queue 1:\n");
                hold_display(headh1);
                printf("Hold Queue 2:\n");
                hold_display(headh2);
                printf("Ready Queue:\n");
                ready_display(headready->next);
                printf("Process Running on CPU:\n");
                running_display(running_job);
                printf("Waiting Queue\n");
                ready_display(headwait);
            }*/
            if (strcmp(token,"D")==0){
                printf("At time %s",line+2);
                printf("Current Available Main Memory: %d\n",remaining_memory);
                printf("Current Devices: %d\n",remaining_devices);
                printf("Completed Jobs:\n");
                finish_display(headfinish);
                printf("Hold Queue 1:\n");
                hold_display(headh1);
                printf("Hold Queue 2:\n");
                hold_display(headh2);
                printf("Ready Queue:\n");
                ready_display(headready->next);
                printf("Process Running on CPU:\n");
                running_display(running_job);
                printf("Waiting Queue\n");
                ready_display(headwait);
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
                }  
                else if (run_count==quantum){
                    running_job=NULL;
                    Node *temp = pop(headready);
                    cpu_to_ready(headready,temp);
                    running_job=headready;
                } 
            }
            //Check wait queue if requests can be granted upon device release
            if(headwait->job != NULL){
                Node *wait_node = headwait; 
                while(wait_node->job != NULL){
                    if(grantRequest(wait_node->job->pending_request, wait_node) == 1){
                        //Push to ready queue if safe, granting request in the process
                        wait_node->job->pending_request = 0; 
                        wait_node = wait_node->next; 
                        Node *temp2 = pop(wait_node->prev);
                        push_helper(headready, temp2);
                    }
                    else {
                        wait_node = wait_node->next; 
                    }
                }
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
                run_count=1;
            }
            
        }
        
        index++;
    }
}
