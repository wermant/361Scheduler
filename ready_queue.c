#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "hold_queue1.h"
#include "hold_queue2.h"
#include "wait_queue.h"

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

void ready_push(Node *headh1, Node *headh2, Node *headwait, Node *headready, int total_memory, int total_devices){
    if (headwait->job!=NULL){
        if (headwait->job->used_devices <=total_devices && headwait->job->needed_memory<=total_memory){
            Node *temp=pop(headwait);
            push_helper(headready,temp);
        }
    }
    else if (headh1->job!=NULL){
        if (headh1->job->used_devices <=total_devices && headh1->job->needed_memory<=total_memory){
            Node *temp=pop(headh1);
            push_helper(headready,temp);
        }
    }
    else if (headh2->job!=NULL){
        if (headh2->job->used_devices <=total_devices && headh2->job->needed_memory<=total_memory){
            Node *temp=pop(headh2);           
            push_helper(headready,temp);
        }
    }
}