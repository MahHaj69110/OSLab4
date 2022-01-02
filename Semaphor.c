#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "Semaphor.h"

void
wait_semaphor(struct semaphor* sem, struct proc* p){
    sem->value--;
    if (sem->value <0){
        // add this process to sem->list
        // sem->sleep_proc_queu[sem->last_proc_in_queue_index+1]= p->pid;
        sem->sleep_proc_queu[sem->last_proc_in_queue_index+1] = p;  // if list is proc*
        sem->last_proc_in_queue_index++;
        p->state= SLEEPING;
    }
}

void
signal_semaphor(struct semaphor* sem){
    sem->value++;
    if (sem->value <=0){
        //remove a process p from sem->list
        //wakeup(p)
        struct proc* p;
        // for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
        //     if (p->pid== sem->sleep_proc_queu[0])
        //         break;
        p= sem->sleep_proc_queu[0];// if list is proc*
        for (int i= 0; i< sem->last_proc_in_queue_index; i++){
            sem->sleep_proc_queu[i]= sem->sleep_proc_queu[i+1];
        }
        sem->last_proc_in_queue_index--;
        p->state= RUNNABLE;
    }
}
void
sem_init(int i, int v){
    semaphor_locks[i].value= v;
    semaphor_locks[i].last_proc_in_queue_index = -1;
}
void
sem_acquire(int i){
    wait_semaphor(&semaphor_locks[i], myproc());
}
void
sem_release(int i){
    signal_semaphor(&semaphor_locks[i]);
}