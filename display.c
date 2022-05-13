#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void display(Node *head){
    while (head->job!=NULL){
        printf("%d\t%d\t%d\t%d\t%d\n", head->job->job_num, head->job->arrival,head->job->total_time, head->job->acquired_time, head->job->run_time);
        if (head->next!=NULL){
            head=head->next;
        }
        else{
            break;
        }
    }
}