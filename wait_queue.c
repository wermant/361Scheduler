#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "wait_queue.h"

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
        return head;
    }
}

Node *wait_pop(Node *head){
    Node *ret = head;
    head=head->next;
    head->prev=NULL;
    ret->next=NULL;
    return ret;
}