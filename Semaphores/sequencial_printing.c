#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define N (5)
sem_t th_sem[N];

void* pth_func(void* argu){
    int itr = *((int *)argu);
    int i = itr;

    printf("The thread created is %d ...\n", itr);
    while (1) {
        sem_wait(&th_sem[i%N]);
        printf("Number is %d. \n", itr);
        sem_post(&th_sem[(i+1)%N]);
        itr +=N;
        usleep(500000);
    }

    return NULL;
}

int main(){
    // init the threads
    pthread_t pth[N];

    // init the arguemnts 
    int argu[N] = {0,1,2,3,4};

    // init the semaphores for sync of the std print medium
    sem_init(&th_sem[0], 0, 1);
    for(int i = 1; i < N; i++){
        sem_init(&th_sem[i], 0, 0);
    }

    // create the threads
    printf("Created the threads ...\n");
    for(int i = 0; i < N; i++){
        pthread_create(&pth[i], NULL, pth_func, (void*)&argu[i]);
    }

    // join the threads
    printf("Joined the threads ...\n");
    for(int i = 0; i < N; i++){
        pthread_join(pth[i], NULL);
    }

    // return

    return 0;

}