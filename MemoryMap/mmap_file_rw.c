#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE (1<<12)

int main(){

    int fd = open("foo.txt", O_RDWR);

    lseek(fd, 0, SEEK_SET);

    ftruncate(fd, PAGE_SIZE);
    
    char* m_ptr = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(m_ptr == MAP_FAILED){

        printf("Mapping failed!!!\n");
    }

    char rdata[10] = "ABCDEFGHI\n";
    int i = 80;
    while(i--){
        memcpy((void*)m_ptr, (void*)rdata, 10);
      //  printf("READ: %s", rdata);
       // memset((void*)rdata, 0, 50);
        m_ptr = m_ptr+10;
    }

    munmap(m_ptr, PAGE_SIZE);
    close(fd);

    return 0;
}