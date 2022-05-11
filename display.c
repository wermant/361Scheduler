#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void display(Node *head){
    while (head!=NULL){
        printf("%d\t%d\t%d\t%d\t%d\n",head->job->job_num,head->job->arrival,head->job->acquired_time,head->job->total_time,head->job->run_time);
        head=head->next;
    }
}