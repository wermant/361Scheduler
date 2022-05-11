#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "queues.h"

void hq1_push(Node *head,Job *new_job,int total_memory,int total_devices){
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return;
    }
    else if (head->job==NULL){
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
        printf("Here\n");
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
            /*new_node->next=temp;
            new_node->prev=NULL;
            temp->prev=new_node;
            temp->next=head->next;
            head=new_node;*/
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

void hq2_push(Node *head, Job *new_job,int total_memory,int total_devices){
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return;
    }
    else if (head->job==NULL){
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{
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

Node *wait_push(Node *head, Node *new_node){
    if (head==NULL){
        head=new_node;
        head->next=NULL;
        head->prev=NULL;
        return head;
    }
    else{
        Node *temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;
    }
}

void push_helper(Node *headready, Node *new_node){
    if (headready->job==NULL){
        headready->job=new_node->job;
        headready->next=NULL;
        headready->prev=NULL;
    }
    else{
        printf("Whatup\n");
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
            push_helper(headready,temp);
            return temp;
        }
    }
    else if (headh2->job!=NULL){
        if (headh2->job->used_devices <=total_devices && headh2->job->needed_memory<=total_memory){
            Node *temp=pop(headh2);           
            push_helper(headready,temp);
            return temp;
        }
    }
}

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