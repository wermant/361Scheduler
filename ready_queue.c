#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

Node *ready_push(Node *headh1, Node *headh2, Node *headwait, int total_memory, int total_devices){

}

Node *push_helper(Node *head, Job *new_job,int total_memory,int total_devices){
    if (new_job->needed_memory > total_memory || new_job->num_devices > total_devices){
        return head;
    }
    if (head==NULL){
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
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=new_node;
        new_node->prev=temp;
        new_node->next=NULL;
        return head;
    }
}