#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

// Printing display for completed jobs: Job ID, arrival time, finish time, and turnaround time
void finish_display(Node *head){
    printf("Completed Jobs:\n");
    printf("--------------------------------------------------------\n");
    printf("Job ID    Arrival Time    Finish Time    Turnaround Time\n");
    printf("========================================================\n");
    while (head->job!=NULL){
        printf("   %d\t\t%d\t\t%d    \t\t%d\n", head->job->job_num, head->job->arrival,head->job->total_time+head->job->arrival, head->job->total_time);
        if (head->next!=NULL){
            head=head->next;
        }
        else{
            break;
        }
    }
    printf("\n");
}

// Printing job ID and run time for each job in hold queues
void hold_display(Node *head){
    printf("--------------------------------------------------------\n");
    printf("Job ID    Run Time\n");
    printf("========================================================\n");
    while (head->job!=NULL){
        printf("   %d\t\t%d\n", head->job->job_num, head->job->run_time);
        if (head->next!=NULL){
            head=head->next;
        }
        else{
            break;
        }
    }
    printf("\n");
}

// Printing job ID, run time, and acquired time for each job in the ready queue and wait queue
void ready_display(Node *head){
    printf("--------------------------------------------------------\n");
    printf("Job ID    Run Time    Time Accrued\n");
    printf("========================================================\n");
    while (head->job!=NULL){
        printf("   %d\t\t%d\t\t%d\n", head->job->job_num, head->job->run_time,head->job->acquired_time);
        if (head->next!=NULL){
            head=head->next;
        }
        else{
            break;
        }
    }
    printf("\n");
}

// Printing job ID, acquired time, and time left for the running job
void running_display(Node *head){
    printf("--------------------------------------------------------\n");
    printf("Job ID    Time Accrued    Time Left\n");
    printf("========================================================\n");
    if (head->job!=NULL){
        printf("   %d\t\t%d\t\t%d\n", head->job->job_num, head->job->acquired_time,head->job->run_time- head->job->acquired_time);
    }
    printf("\n");
}