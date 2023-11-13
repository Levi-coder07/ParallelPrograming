#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int thread_count;
void* Hello(void* rank);
struct list_node_s{
    int data;
    struct list_node_s* next;
   
};
struct list_node_s * head_p;
pthread_mutex_t list_mutex;
int Member(int value ){
    struct list_node_s* curr_p = head_p;
    while (curr_p!=NULL&&curr_p->data<value){
        curr_p = curr_p->next;

    }
    if(curr_p==NULL|| curr_p->data>value){
        printf("NO ENCONTRADO \n");
        return 0;

    }else{
        printf("ENCONTRADO \n");
        return 1;
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
            printf("INSERTADO \n");
        }else{
            pred_p->next = temp_p;
            printf("INSERTADO \n");
        }
        return 1;
    }else{
        printf("EN LISTA \n");
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
    if(curr_p!=NULL&&curr_p->data==value){
        if(pred_p==NULL){
            head_p=curr_p->next;
            free(curr_p);
            printf("ELIMINADO \n");
        }else{
            pred_p->next =curr_p->next;
            free(curr_p);
            printf("ELIMINADO \n");
        }
        return 1;

    }else{
            printf("NO ESTA EN LA LISTA \n");
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
    struct list_node_s* curr_p = head_p;
    
    while(curr_p!=NULL){
        printf("%d -> ",curr_p->data);
        curr_p = curr_p->next;
    }
   
    return 0;
}
void * Hello(void*rank){
    long my_rank = (long) rank;
    int randomval = rand() % 100;
    int random_operation = rand() % 3;
    

    if (random_operation == 0) {
        // Insert
        
        printf("Thread %ld: Inserted %d ", my_rank, randomval);
        Insert(randomval);
    } else if (random_operation == 1) {
        // Delete
        
        printf("Thread %ld: Deleted %d ", my_rank, randomval);
        Delete(randomval);
    } else {
        // Member
        
        printf("Thread %ld: El valor %d ", my_rank, randomval);
        Member(randomval);
    }

    pthread_mutex_unlock(&list_mutex);


/*if(my_rank==0){
            pthread_mutex_lock(&list_mutex);
            Delete(6);
            pthread_mutex_unlock(&list_mutex);
        }
        if(my_rank==1){
            pthread_mutex_lock(&list_mutex);
            printf("AQUI");
            Insert(3);
            pthread_mutex_unlock(&list_mutex);
        }*/
        
        
        
        
        
    
    
    
    return NULL;
}
