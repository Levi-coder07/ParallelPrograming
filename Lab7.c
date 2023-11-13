#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
int thread_count;
int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

sem_t barrier_sem ;
void* Hello(void* rank);
int main(int argc,char * argv[]){
    long thread;
    pthread_t* thread_handles;
    pthread_mutex_init(&mutex,NULL);
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
    pthread_mutex_destroy(&mutex);
    return 0;
}

void * Hello(void*rank){
    long my_rank = (long) rank;
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Hello from thread %ld of %d \n",my_rank,thread_count);
    if(counter==thread_count){
        counter=0;
        pthread_cond_broadcast(&cond_var);
        printf("Libero %ld of %d \n",my_rank,thread_count);
    }else{
        
        while(pthread_cond_wait(&cond_var,&mutex)!=0){
            
        }
        printf("Liberados %ld of %d \n",my_rank,thread_count);
    }
    pthread_mutex_unlock(&mutex);

    //printf("Hello from thread %ld of %d \n",my_rank,thread_count);
    return NULL;
}