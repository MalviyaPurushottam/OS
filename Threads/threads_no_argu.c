#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* th1_func(void* argu){
    int i = 5;
    int *iptr = (int*)malloc(sizeof(int));
    *iptr = 50;
    while (i) {
        printf("this is thread 1 ... \n");
        i--;
        usleep(500000);
    }
    return (void*)iptr;
}


void* th2_func(void* argu){
    int i = 5;
    int *iptr = (int*)malloc(sizeof(int));
    *iptr = 75;
    while (i) {
        printf("this is thread 2 ... \n");
        i--;
        usleep(750000);
    }
    return (void*)iptr;
}

int main(){

    // declare thread variable
    pthread_t pth1, pth2;

    // create the threads 
    printf("threads are created below ... \n");
    pthread_create(&pth1, NULL, th1_func, NULL);
    pthread_create(&pth2, NULL, th2_func, NULL);

    // store the value returned by threads
    int *th1_ret, *th2_ret;

    // join the threads
    printf("Threads are joined below ... \n");
    pthread_join(pth1, (void **)&th1_ret);
    pthread_join(pth2, (void **)&th2_ret);

    // go to end
    printf("This is the end of the main joined threads are returned ... \n");
    printf("Value retruned by thread 1 is %d. \n", *th1_ret);
    printf("Value returned by thread 2 is %d. \n", *th2_ret);

    // freeing the heap memory
    free(th1_ret);
    free(th2_ret);

    return 1;
}