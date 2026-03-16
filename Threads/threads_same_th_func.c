#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct node_t{
    int data;
} node;

void* th_func(void* argu){
    int i = 5;
    node* temp_data = ((node*)argu);
    while (i) {
        printf("this is thread %d ... \n", temp_data->data);
        i--;
        usleep(500000);
    }
    return NULL;
}

int main(){

    // declare thread variable
    pthread_t pth1, pth2;

    // init the arguments
    node th1_argu, th2_argu;
    th1_argu.data = 1;
    th2_argu.data = 2;

    // create the threads 
    printf("threads are created below ... \n");
    pthread_create(&pth1, NULL, th_func, (void*)&th1_argu);
    pthread_create(&pth2, NULL, th_func, (void*)&th2_argu);

    // join the threads
    printf("Threads are joined below ... \n");
    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    // go to end
    printf("This is the end of the main joined threads are returned ... \n");

    return 1;
}