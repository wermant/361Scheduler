#include "structures.h"
typedef struct Node{
    Job *job;
    Node *next;
    Node *prev;
}Node;

void push(Node *,Job *);
Node *pop(Node *);

