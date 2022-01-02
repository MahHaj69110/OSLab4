#define MAX_SLEEPING_IN_SEMAPHOR 10
#define SEMAPHOR_NUM_IN_SYSTEM 5

struct semaphor
{
    int value;
    int last_proc_in_queue_index;  // initialize to -1
    int sleep_proc_queu [MAX_SLEEPING_IN_SEMAPHOR];
    //struct proc*  sleep_proc_queu [MAX_SLEEPING_IN_SEMAPHOR];
};


struct semaphor semaphor_locks[SEMAPHOR_NUM_IN_SYSTEM];
int chopstick[SEMAPHOR_NUM_IN_SYSTEM];


void sem_init(int i, int v);
void sem_acquire(int i);
void sem_release(int i);
void wait_semaphor(struct semaphor* sem, struct proc* p);
void signal_semaphor(struct semaphor* sem);