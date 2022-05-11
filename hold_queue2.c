

Node *push(Node *head, Job *new_job){
    if (head==NULL){
        head=malloc(sizeof(Node));
        head->job=new_job;
        head->next=NULL;
        head->prev=NULL;
        return head;
    }
    else{
        Node *new_node=malloc(sizeof(Node));
        new_node->job=new_job;
        Node *temp=head;
        while (temp->next != NULL){
            temp=temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
        new_node->next = NULL;
        return head;
    }
}

Node *pop(Node *head){
    Node *ret = head;
    head=head->next;
    head->prev=NULL;
    ret->next = NULL;
    return ret;
}
