#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* th1_func(void* argu){
    int i = 5;
    while (i) {
        printf("this is thread 1 ... \n");
        i--;
        usleep(500000);
    }
    return NULL;
}


void* th2_func(void* argu){
    int i = 5;
    while (i) {
        printf("this is thread 2 ... \n");
        i--;
        usleep(750000);
    }
    return NULL;
}

int main(){

    // declare thread variable
    pthread_t pth1, pth2;

    // create the threads 
    printf("threads are created below ... \n");
    pthread_create(&pth1, NULL, th1_func, NULL);
    pthread_create(&pth2, NULL, th2_func, NULL);

    // join the threads
    printf("Threads are joined below ... \n");
    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    // go to end
    printf("This is the end of the main joined threads are returned ... \n");

    return 1;
}