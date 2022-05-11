void hq1_push(Node *,Job *,int, int);
void hq2_push(Node *,Job *,int,int);
Node * wait_push(Node *,Node *);
Node * ready_push(Node *headh1, Node *headh2, Node *headwait, Node *headready, int total_memory, int total_devices);
void push_helper(Node *, Node *);
void updateTime(Node *,Node *,Node *, Node *);
Node *pop(Node *);