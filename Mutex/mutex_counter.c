#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

long counter = 0;
pthread_mutex_t mut_counter;

void* pth_func(void* argu){

    for(long i =0; i< 1000000; i++){
        while(pthread_mutex_trylock(&mut_counter)){
            usleep(rand()%100000);
        }
        counter++;
        pthread_mutex_unlock(&mut_counter);
    }

    return NULL;
}
int main(){
    
    // init 2 threads
    pthread_t pth1, pth2;

    // init the mutex 
    pthread_mutex_init(&mut_counter, NULL);

    // create the threads
    pthread_create(&pth1, NULL, pth_func, NULL);
    pthread_create(&pth2, NULL, pth_func, NULL);

    // join them
    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    printf("Counter value at the end is %ld ... \n", counter);

    return 0;
 }