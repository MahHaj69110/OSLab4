#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#include "Semaphor.h"

int
main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < 5; i++) {
        sem_init(i, 1);
        chopstick[i] = -1;
    }

    int Ps_pid[5];
    for(i = 0; i < 5; i++){
        int pid = fork();
        if(pid == 0){
            exec("Philosopher", argv);
        }
        else {
            // Ps_pid[i] = pid;
        }
    }
}