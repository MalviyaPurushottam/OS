#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* th1_func(void* argu){

    pthread_detach(pthread_self());
    int i = 5;
    while (1) {
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

    //set the attributes of one thread
    pthread_attr_t pth1_attr;
    pthread_attr_setdetachstate(&pth1_attr, PTHREAD_CREATE_DETACHED);

    // create the threads 
    printf("threads are created below ... \n");
    pthread_create(&pth1, NULL, th1_func, NULL);
    pthread_create(&pth2, NULL, th2_func, NULL);

    // join the threads
    printf("Threads are joined below ... \n");
    //pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    // go to end
    printf("This is the end of the main joined threads are returned ... \n");
    sleep(5);
    return 1;
}