typedef struct Job{
    int arrival;
    int job_num;
    int needed_memory;
    int num_devices;
    int run_time;
    int priority;
    int used_devices;
    int acquired_time;
    int total_time;
}Job;

Job * createJob(char str[]);
void destroyJob(Job *);

typedef struct Request{
    int arrival;
    int job_num;
    int num_devices;
}Request;

Request * createRequest(char str[]);
void destroyRequest(Request *);

typedef struct Release{
    int release_time;
    int job_num;
    int num_devices;
}Release;

Release * createRelease(char str[]);
void destroyRelease(Release *);

typedef struct Node{
    Job *job;
    struct Node *next;
    struct Node *prev;
}Node;

void destroyNode(Node *);