#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "hold_queue1.h"
#include "hold_queue2.h"
#include "wait_queue.h"

Node *ready_push(Node *headh1, Node *headh2, Node *headwait, Node *headready, int total_memory, int total_devices){
    if (headwait!=NULL){
        if (headwait->job->used_devices <=total_devices && headwait->job->needed_memory<=total_memory){
            return push_helper(headready,headwait);
        }
    }
}

Node *push_helper(Node *headready, Node *new_node){
    if (headready==NULL){
        headready=new_node;
        headready->next=NULL;
        headready->prev=NULL;
        return headready;
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