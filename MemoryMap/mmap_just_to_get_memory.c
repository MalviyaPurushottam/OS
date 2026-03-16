#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define PAGE_SIZE (1<<12) // 4 KB
int main(){

    // trying the mmap just for fun
    int *memo_ptr = mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    int *reader_ptr = memo_ptr;
    int *write_ptr = memo_ptr;

    char* data[] = {"Aaaaaaaaaa", 
                      "Bbbbbbbbbb", 
                      "Cccccccccc", 
                      "Dddddddddd",
                      "Eeeeeeeeee"};

    printf("now writing data to the file %p %p %p... \n", memo_ptr, reader_ptr, write_ptr);
    for(int i = 0; i < 5; i++){
        memcpy((void*)memo_ptr, (void*)data[i], 10);
        memo_ptr = (int*)((char*)memo_ptr+10);
    }

    char get[100] = {0};
    for(int i = 0; i< 10; i++){
        memcpy(get, reader_ptr, 5);
        printf("Data read is %s ... \n", get);
        printf("Size of the string is %ld ... \n", strlen(get));
        reader_ptr = (int*)((char*)reader_ptr+5);
    }

    munmap(memo_ptr, PAGE_SIZE);
    return 0;
}