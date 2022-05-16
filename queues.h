// File Declarations used in queues.c
Node *init();
void hq1_push(Node *,Job *,int, int);
void hq2_push(Node *,Job *,int,int);
void wait_push(Node *,Node *);
Node * ready_push(Node *headh1, Node *headh2, Node *headwait, Node *headready, int total_memory, int total_devices);
void push_helper(Node *, Node *);
void updateTime(Node *,Node *,Node *, Node *);
void finish_push(Node *,Node *);
void cpu_to_ready(Node *,Node *);
Node *pop(Node *);
float avg_turnaround(Node *);