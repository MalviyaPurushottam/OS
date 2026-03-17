#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>


#include "header.h"

int main(){

    int w_fd = open(COMMON_FILE_NAME, O_CREAT|O_RDWR, 0660);
    if(w_fd<0){
        printf("File is not opened !!! %d", w_fd);
    }

    ftruncate(w_fd, PAGE_SIZE);
    sem_unlink(WRITE_SEMA_NAME);
    sem_unlink(READ_SEMA_NAME);
    // init the semaphore
    sem_t *w_sem = sem_open(WRITE_SEMA_NAME, O_CREAT, 0660, 1);
    sem_t *r_sem = sem_open(READ_SEMA_NAME, O_CREAT, 0660, 0);  

    char* w_ptr = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, w_fd, 0);
    if(w_ptr == MAP_FAILED){
        printf("Mapping error!!! %p \n", w_ptr);
    }

    char w_data[100];
    long itr = 0;
    while(1){
        sprintf(w_data, "The data written is this number of times %ld ... \n", itr++);
        sem_wait(w_sem);
        memcpy((void*)w_ptr, (void*)w_data, 60);
        sem_post(r_sem);
        usleep(1000000);
    }

    munmap(w_ptr, PAGE_SIZE);
    sem_close(w_sem);
    sem_close(r_sem);
    close(w_fd);

    return 0;
}