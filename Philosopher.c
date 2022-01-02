#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#include "Semaphor.h"
#include "spinlock.h"

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[SEMAPHOR_NUM_IN_SYSTEM];
// int phil[SEMAPHOR_NUM_IN_SYSTEM] = { 0, 1, 2, 3, 4 };
 
// sem_t mutex;

void check(int phil_num)
{
    if (state[phil_num] == HUNGRY
        && state[(phil_num+4)%5] != EATING
        && state[(phil_num+1)%5] != EATING) {
        // state that eating
        state[phil_num] = EATING;
 
        chopstick[(phil_num+4)%5] = phil_num;
        chopstick[phil_num] = phil_num;
        // printf("Philosopher %d takes fork %d and %d\n", phil_num, (phil_num+4)%5, phil_num);

        // printf("Philosopher %d is Eating\n", phil_num);
        sleep(2000);
 
        chopstick[(phil_num+4)%5] = -1;
        chopstick[phil_num] = -1;
        // sem_post(&S[phil_num]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_release(phil_num);
    }
}

// take up chopsticks
void pickup(int phil_num)
{
    
    
    // sem_wait(&mutex);
 
    // state that hungry
    state[phil_num] = HUNGRY;
 
    // printf("Philosopher %d is Hungry\n", phil_num);
 
    // eat if neighbours are not eating
    check(phil_num);
 
    // sem_post(&mutex);
 
    // if unable to eat wait to be signalled
    sem_acquire(phil_num);
 
    sleep(1000);
}
 
// put down chopsticks
void putdown(int phil_num)
{
 
    // sem_wait(&mutex);
 
    // state that thinking
    state[phil_num] = THINKING;
 
    // printf("Philosopher %d putting fork %d and %d down\n",
        //    phil_num, (phil_num+4)%5, phil_num);
    // printf("Philosopher %d is thinking\n", phil_num);
 
    check((phil_num+4)%5);
    check((phil_num+1)%5);
 
    // sem_post(&mutex);
}

int
main(int argc, char *argv[])
{
    int phil_num = getpid() - 2;
    // printf(1, phil_num); // = ?
    while(1) {
        sleep(1000);
        pickup(phil_num);
        sleep(500);
        putdown(phil_num);
    }
}