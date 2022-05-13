#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "queues.h"

// Job initialization
Node *init(){
    Node *head=malloc(sizeof(Node));
    head->job=NULL;
    head->next=NULL;
    head->prev=NULL;
    return head;
}

// Hold Queue 1: Shortest Job First (SJF)
// Push: Determining where job will be placed in Hold Queue 1
void hq1_push(Node *head,Job *new_job,int total_memory,int total_devices){
    // New job cannot be placed in queue if its main memory or devices is greater than the available space
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return;
    }
    else if (head->job==NULL){
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
        fflush(stdout);
    }
    else{
        Node *new_node=malloc(sizeof(Node));
        new_node->job=new_job;
        Node *temp=head;
        while (temp->job->run_time<=new_node->job->run_time&&temp->next!=NULL){
            temp=temp->next;
        }
        if (temp==head && temp->job->run_time>new_node->job->run_time&&temp->next==NULL){
            Job *temp_job=head->job;
            head->job=new_node->job;
            new_node->job=temp_job;
            head->next=new_node;
            new_node->prev=head;
            new_node->next=NULL;
        }
        else if (temp==head && temp->job->run_time>new_node->job->run_time&&temp->next!=NULL){
            Job *temp_job=head->job;
            head->job=new_node->job;
            new_node->job=temp_job;
            head->next->prev=new_node;
            head->next=new_node;
            new_node->prev=head;
        }
        else if(temp==head&&temp->job->run_time<=new_node->job->run_time&&temp->next==NULL){
            new_node->prev=temp;
            new_node->next=NULL;
            temp->next=new_node;
        }
        else if (temp->next==NULL&&temp->job->run_time<=new_node->job->run_time){
            temp->next=new_node;
            new_node->prev=temp;
            new_node->next=NULL;
        }
        else{
            new_node->next=temp;
            new_node->prev=temp->prev;
            temp->prev->next=new_node;
            temp->prev=new_node;
        }
    }
}

// Hold Queue 2: First In First Out (FIFO)
// Push: Determining where job will be placed in Hold Queue 2
void hq2_push(Node *head, Job *new_job,int total_memory,int total_devices){
    // New job cannot be placed in queue if its main memory or devices is greater than the available space
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return;
    }
    else if (head->job==NULL){
        // hold queue is empty, current job will be first in queue
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{ // sets current job at the end of the queue
        Node *new_node=malloc(sizeof(Node));
        new_node->job=new_job;
        Node *temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;
    }
}

// Wait Queue: Jobs will enter wait queue until the ready queue has the space for them
// Push: Determining where job will be placed in Wait Queue
void wait_push(Node *head, Node *new_node){
    if (head->job==NULL){
        // wait queue is empty, current job will be first in queue
        head->job=new_node->job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{
        // sets current job at the end of the queue
        Node *temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;
    }
}

// 
void push_helper(Node *headready, Node *new_node){
    if (headready->job==NULL){
        headready->job=new_node->job;
        headready->next=NULL;
        headready->prev=NULL;
    }
    else{
        Node *temp=headready;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        if (temp==headready){
            headready->next=new_node;
            new_node->prev=headready;
            new_node->next=NULL;
        }
        else{
            temp->next=new_node;
            new_node->prev=temp;
            new_node->next=NULL;
        }
    }
}

// Ready Queue: Process is placed in ready queue before entering the CPU
// Push: Determining where the job will be placed in ready queue
Node* ready_push(Node *headh1, Node *headh2, Node *headwait, Node *headready, int total_memory, int total_devices){
    if (headwait->job!=NULL){
        if (headwait->job->used_devices <=total_devices && headwait->job->needed_memory<=total_memory){
            Node *temp=pop(headwait);
            push_helper(headready,temp);
            return temp;
        }
    }
    else if (headh1->job!=NULL){
        if (headh1->job->used_devices <=total_devices && headh1->job->needed_memory<=total_memory){
            Node *temp=pop(headh1);
            //printf("Popped Job %d from HQ1\n", temp->job->job_num);
            push_helper(headready,temp);
            return temp;
        }
    }
    else if (headh2->job!=NULL){
        if (headh2->job->used_devices <=total_devices && headh2->job->needed_memory<=total_memory){
            Node *temp=pop(headh2);        
            //printf("Popped Job %d from HQ2\n", temp->job->job_num);   
            push_helper(headready,temp);
            return temp;
        }
    }
    else{
        return NULL;
    }
}

// 
void updateTime(Node *headh1, Node *headh2, Node *headwait, Node *headready){
    while (headh1->job!=NULL){
        headh1->job->total_time+=1;
        if (headh1->next!=NULL){
            headh1=headh1->next;  
        }
        else{
            break;
        }
    }
    while (headh2->job!=NULL){
        headh2->job->total_time+=1;
        if (headh2->next!=NULL){
            headh2=headh2->next;  
        }
        else{
            break;
        }
    }while (headwait->job!=NULL){
        headwait->job->total_time+=1;
        if (headwait->next!=NULL){
            headwait=headwait->next;  
        }
        else{
            break;
        }
    }
    while (headready->job!=NULL){
        headready->job->total_time+=1;
        if (headready->next!=NULL){
            headready=headready->next;  
        }
        else{
            break;
        }
    }
}

// 
void finish_push(Node *head,Node *new_node){
    if (head->job==NULL){
        head->job=new_node->job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{
        /*Node *temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;*/
        Node *temp=head;
        while (temp->job->job_num<=new_node->job->job_num&&temp->next!=NULL){
            temp=temp->next;
        }
        if (temp==head && temp->job->job_num>new_node->job->job_num&&temp->next==NULL){
            Job *temp_job=head->job;
            head->job=new_node->job;
            new_node->job=temp_job;
            head->next=new_node;
            new_node->prev=head;
            new_node->next=NULL;
        }
        else if (temp==head && temp->job->job_num>new_node->job->job_num&&temp->next!=NULL){
            Job *temp_job=head->job;
            head->job=new_node->job;
            new_node->job=temp_job;
            head->next->prev=new_node;
            head->next=new_node;
            new_node->prev=head;
        }
        else if(temp==head&&temp->job->job_num<=new_node->job->job_num&&temp->next==NULL){
            new_node->prev=temp;
            new_node->next=NULL;
            temp->next=new_node;
        }
        else if (temp->next==NULL&&temp->job->job_num<=new_node->job->job_num){
            temp->next=new_node;
            new_node->prev=temp;
            new_node->next=NULL;
        }
        else{
            new_node->next=temp;
            new_node->prev=temp->prev;
            temp->prev->next=new_node;
            temp->prev=new_node;
        }
    }
}

void cpu_to_ready(Node *head,Node *new_node){
    if (head->job==NULL){
        // wait queue is empty, current job will be first in queue
        head->job=new_node->job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{
        // sets current job at the end of the queue
        Node *temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;
    }
}

// Pop: Removing a job from its current queue when able to
Node *pop(Node *head){
    Node *ret=malloc(sizeof(Node));
    if (head->next==NULL){
        ret->job=head->job;
        head->job=NULL;
        return ret;
    }
    else{
        Job *temp_job=head->job;
        ret->job=head->job;
        head->job=head->next->job;
        head->next=head->next->next;
        return ret; 
    }
}