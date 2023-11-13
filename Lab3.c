#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
int thread_count;
int counter = 0;
pthread_mutex_t barrier_mutex;
sem_t count_sem ;

sem_t barrier_sem ;
void* Hello(void* rank);
int main(int argc,char * argv[]){
    long thread;
    sem_init(&count_sem,0,1);
    sem_init(&barrier_sem,0,0);
    pthread_t* thread_handles;
    pthread_mutex_init(&barrier_mutex,NULL);
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
    sem_wait(&count_sem);
    if(counter == thread_count-1){
        counter = 0;
        sem_post(&count_sem);
        printf("Liberando procesos %ld of %d \n",my_rank,thread_count);
        for(int j=0;j<thread_count-1;j++){
            sem_post(&barrier_sem);
            
        }

    }else{
        counter++;
        printf("Hello from thread %ld of %d \n",my_rank,thread_count);
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
        printf("Volviendo a ejecutarme Hello from thread %ld of %d \n",my_rank,thread_count);
        
    }
    //printf("Hello from thread %ld of %d \n",my_rank,thread_count);
    return NULL;
}