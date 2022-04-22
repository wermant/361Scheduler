#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "hold_queue1.h"
void push(Node *head,Job *new_job){
    if (head==NULL){
        head=malloc(sizeof(Node));
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
    }
    else{
        Node *new_node=malloc(sizeof(Node));
        new_node->job=new_job;
        Node *temp=head;
        while ((temp->job->run_time <= new_node->job->run_time)&&(temp->next->job->run_time>=new_node->job->run_time)){
            temp=temp->next;
        }
        temp->next->prev=new_node;
        new_node->next=temp->next;
        new_node->prev=temp;
        temp->next=new_node;
    }
}

Node *pop(Node *head){
    Node *ret = head;
    head=head->next;
    head->prev=NULL;
    return ret;
}

