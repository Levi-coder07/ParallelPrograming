#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int thread_count;
void* Hello(void* rank);
struct list_node_s {
    int data;
    struct list_node_s *next;
    pthread_mutex_t mutex;
};

struct list_node_s *head_p;
pthread_mutex_t head_p_mutex;
int Member(int value) {
    struct list_node_s *temp_p;
    pthread_mutex_lock(&head_p_mutex);
    temp_p = head_p;

    while (temp_p != NULL && temp_p->data < value) {
        if (temp_p->next != NULL) {
            pthread_mutex_lock(&(temp_p->next->mutex));
        }

        if (temp_p == head_p) {
            pthread_mutex_unlock(&head_p_mutex);
        }

        pthread_mutex_unlock(&(temp_p->mutex));
        temp_p = temp_p->next;
    }

    if (temp_p == NULL || temp_p->data > value) {
        if (temp_p == head_p) {
            pthread_mutex_unlock(&head_p_mutex);
        }

        if (temp_p != NULL) {
            pthread_mutex_unlock(&(temp_p->mutex));
        }

        return 0;  // Not found
    } else {
        if (temp_p == head_p) {
            pthread_mutex_unlock(&head_p_mutex);
        }

        pthread_mutex_unlock(&(temp_p->mutex));
        return 1;  // Found
    }
}

int Insert(int value){
    struct list_node_s* curr_p = head_p;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;
    while(curr_p!=NULL&&curr_p->data<value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p==NULL|| curr_p->data>value){
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if(pred_p==NULL){
            head_p = temp_p;
        }else{
            pred_p->next = temp_p;
        }
        return 1;
    }else{
        return 0;
    }
}
int Delete(int value){
    struct list_node_s* curr_p = head_p;
    struct list_node_s* pred_p = NULL;
    while(curr_p!=NULL&&curr_p->data<value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if(curr_p==NULL&&curr_p->data==value){
        if(pred_p==NULL){
            head_p=curr_p->next;
            free(curr_p);

        }else{
            pred_p->next =curr_p->next;
            free(curr_p);
        }
        return 1;

    }else{
        return 0;
    }
}
int main(int argc,char * argv[]){
    long thread;
    srand((unsigned int)time(NULL));
    pthread_t* thread_handles;
    for (int i = 0; i < 50; i++) {
        int randomval = rand() % 100;  // Adjust the range as needed
        Insert(randomval);
    }
    
    thread_count = strtol(argv[1],NULL,10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));
    for(thread=0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,Hello,(void*)thread);
    }
    //printf("Hello from the main thread\n");
    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }
    free(thread_handles);
    return 0;
}
void * Hello(void*rank){
    long my_rank = (long) rank;
     int randomval = rand() % 100;
    printf("Thread %ld: El valor %d \n", my_rank, randomval);
    Member(randomval);
        
    return NULL;
}
