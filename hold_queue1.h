typedef struct Node{
    Job *job;
    struct Node *next;
    struct Node *prev;
}Node;

Node *push(Node *,Job *);
Node *pop(Node *);

