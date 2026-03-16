#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define N (5)
int data[10] = {0,1,2,3,4,5,6,7,8,9};
// declare the rwlock
pthread_rwlock_t rw_data_lock;

void* pth_w_func(void* argu){

    while(1){
        pthread_rwlock_wrlock(&rw_data_lock);
        for (int i = 0; i < 10; i++) {
            data[i]+=1;
        }
        pthread_rwlock_unlock(&rw_data_lock);
        //usleep(1);
    }

    return NULL;
}

void* pth_r_func(void* argu){

    int iptr = *((int *)argu);
    while (1) {
        pthread_rwlock_rdlock(&rw_data_lock);
        printf("Thread %d: values read at the index are %d and %d. The difference is %d ... \n", iptr, data[iptr], data[iptr+5], (data[iptr+5]-data[iptr]));
        pthread_rwlock_unlock(&rw_data_lock);
        usleep(1);
    }

    return NULL;
}

int main(){

    // init the thread variable
    pthread_t pth_w, pth_r[N];
    int index[] = {0,1,2,3,4};

    // init the rw lock
    pthread_rwlock_init(&rw_data_lock, NULL);

    // create those threads
    pthread_create(&pth_w, NULL, pth_w_func, NULL);
    for(int i = 0; i < N; i++){
        pthread_create(&pth_r[i], NULL, pth_r_func, (void*)(&(index[i])));
    }
    
    // join them 
    pthread_join(pth_w, NULL);
    for(int i = 0; i < N; i++){
        pthread_join(pth_r[i], NULL);
    }

    // destroy the rwlock
    pthread_rwlock_destroy(&rw_data_lock);
    
    return 0;
}