typedef struct System{
    int start_time;
    int main_memory;
    int serial_devices;
    int quantum;
}System;

System * createSystem(char str[]);
void destroySystem(System *);

typedef struct Job{
    int arrival;
    int job_num;
    int needed_memory;
    int num_devices;
    int run_time;
    int priority;
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