#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "hold_queue1.h"

Node *hq1_push(Node *head,Job *new_job,int total_memory,int total_devices, int total_devices){
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return head;
    }
    else if (head==NULL){
        head=malloc(sizeof(Node));
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
        return head;
    }
    else{
        Node *new_node=malloc(sizeof(Node));
        new_node->job=new_job;
        Node *temp=head;
        while (temp->job->run_time<=new_node->job->run_time&&temp->next!=NULL){
            temp=temp->next;
        }
        if (temp==head && temp->job->run_time>new_node->job->run_time){
            new_node->next=temp;
            new_node->prev=NULL;
            temp->prev=new_node;
            temp->next=head->next;
            return new_node;
        }
        else if(temp==head&&temp->job->run_time<=new_node->job->run_time&&temp->next==NULL){
            new_node->prev=temp;
            new_node->next=NULL;
            temp->next=new_node;
            return head;
        }
        else if (temp->next==NULL&&temp->job->run_time<=new_node->job->run_time){
            temp->next=new_node;
            new_node->prev=temp;
            new_node->next=NULL;
            return head;
        }
        else{
            new_node->next=temp;
            new_node->prev=temp->prev;
            temp->prev->next=new_node;
            temp->prev=new_node;
            return head;
        }
    }
}

Node *hq1_pop(Node *head){
    Node *ret = head;
    head=head->next;
    head->prev=NULL;
    ret->next=NULL;
    return ret;
}

