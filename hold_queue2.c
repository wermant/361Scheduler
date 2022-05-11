#include <stdlib.h>
#include "structures.h"
#include "hold_queue2.h"

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