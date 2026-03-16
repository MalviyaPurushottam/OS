#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef struct node_t{
    int data;
    struct node_t* prev;
} llnode;

typedef struct {
    pthread_mutex_t head_lock;
    llnode* head;
}list;

list* ll_create(void);
list* ll_add(list* node, int data);
int ll_give(list* node);
list* ll_remove_element(list* node);

void* pth_add_func(void* argu){
    printf("Adder: address of the argument is %p ...\n", argu);


    list* list_head = (list*)argu;
    printf("Adder: address of the list head is %p ...\n", list_head);

    int ite = 0;
    printf("This is a adder thread it will add the elements in the linked list after every interval of 500ms ... \n");
    while(1){
        printf("Adder: %d\n", ite);
        ll_add(list_head, ite);
        ite ++;
        usleep(500000);
    }

    return NULL;
}


void* pth_take_func(void* argu){
    printf("Taker: value of argument is %p ...\n", argu);

    list* list_head = (list*)argu;
    printf("Taker: address of the list head is %p ...\n", list_head);

    int ite;
    printf("This is a taker thread it will add the elements in the linked list after every interval of 600ms ... \n");
    while(1){
        ite = ll_give(list_head);
        printf("Taker: %d\n", ite);
        list_head = ll_remove_element(list_head);
        usleep(1000000);
    }

    return NULL;
}

int main(){

    pthread_t pth_adder, pth_taker;

    list* ll = ll_create();
    printf("Main: address of the ll node is %p ...\n", ll);

    pthread_create(&pth_adder, NULL, pth_add_func, (void*)ll);
    pthread_create(&pth_taker, NULL, pth_take_func, (void*)ll);

    pthread_join(pth_adder, NULL);
    pthread_join(pth_taker, NULL);

    return 1;
}

list* ll_create(void){
    list* node = (list*)malloc(sizeof(list));

    node->head = NULL;
    pthread_mutex_init(&(node->head_lock), NULL);

    return node;
}

list* ll_add(list* node, int data){
    llnode* node_data = (llnode*)malloc(sizeof(llnode));
    node_data->data = data;

    pthread_mutex_lock(&node->head_lock);
    node_data->prev = node->head;
    node->head = node_data;
    pthread_mutex_unlock(&node->head_lock);
    
    return node;
}

int ll_give(list* node){
    if(node->head == NULL){
        return -1;
    }
    return node->head->data;
}

list* ll_remove_element(list* node){
    llnode* node_data = (llnode*)malloc(sizeof(llnode));
    if(node->head == NULL){
        return node;
    }

    pthread_mutex_lock(&node->head_lock);
    node_data = node->head;
    node->head = node->head->prev;
    pthread_mutex_unlock(&node->head_lock);
    
    free(node_data);

    return node;

}