#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    int fd = open("foo.txt", O_CREAT|O_RDWR|O_TRUNC, 0600);

    lseek(fd, 0, SEEK_SET);
    
    char* data = "This is the data written to file\n";
    for(int i = 0; i<10; i++){
        write(fd, data, 33);
    }

    char rdata[50];
    lseek(fd, 0,SEEK_SET);
    for(int i = 0; i< 10; i++){
        read(fd, rdata, 33);
        printf("READ: %s", rdata);
        memset((void*)rdata, 0, 50);
        printf("TELL: file is at %ld ... \n", lseek(fd, 0, SEEK_CUR));
    }

    ftruncate(fd, 33);
    close(fd);

    return 0;
}