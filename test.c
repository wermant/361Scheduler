#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "hold_queue2.h"

Node *h2head=NULL;

void main(){   
    FILE *fp;
    char *line=NULL;
    size_t len=0;
    ssize_t read;

    fp = fopen("test.txt", "r");
    while (getline(&line,&len,fp)!=-1){
        Job *j=createJob(line);
        h2head=push(h2head,j);
    }
    Node *temp=h2head;
    while (temp!=NULL){
        printf("%d\n",temp->job->run_time);
        temp=temp->next;
    }
    fclose(fp);
}