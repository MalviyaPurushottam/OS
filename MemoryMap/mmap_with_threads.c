#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE (1<<12) // 4 Kb size

void* pth_write_func(void* argu){
    char* mptr = (char*)argu;
    long i = 0;
    char string[5] = {0};
    while(1){
        memcpy((void*)string, (void*)&i, 4);
        sprintf(mptr, "The data is added here\n");
        i++;
    }
    return NULL;
}

void* pth_read_func(void* argu){
    char* mptr = (char*)argu;

    while(1){
        printf("READ: %s", mptr);    
    }

    return NULL;
}

int main(){
    // create the shared memory
    char* memo_ptr = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);

    // init 2 threads
    pthread_t pth_read, pth_write;
    
    pthread_create(&pth_read, NULL, pth_read_func, (void*)memo_ptr);
    pthread_create(&pth_write, NULL, pth_write_func, (void*)memo_ptr);

    pthread_join(pth_write, NULL);
    pthread_join(pth_read, NULL);

}
