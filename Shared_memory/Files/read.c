#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>


#include "header.h"

int main(){

    int r_fd = open(COMMON_FILE_NAME, O_RDWR);

    char* r_ptr = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, r_fd, 0);
  
    // init the semaphore
    sem_t *w_sem = sem_open(WRITE_SEMA_NAME, 0);
    sem_t *r_sem = sem_open(READ_SEMA_NAME,  0);  

    char r_data[100];
    while(1){
        sem_wait(r_sem);
        memcpy(r_data, r_ptr, 60);
        sem_post(w_sem);
        printf("READ: %s", r_data);
        usleep(500000);
    }

    munmap(r_ptr, PAGE_SIZE);
    close(r_fd);
    sem_close(w_sem);
    sem_close(r_sem);

    return 0;
}