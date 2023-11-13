#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int thread_count;
int counter;
pthread_mutex_t barrier_mutex;

void* Hello(void* rank);
int main(int argc,char * argv[]){
    long thread;
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
    pthread_mutex_lock(&barrier_mutex);
    counter++;
    pthread_mutex_unlock(&barrier_mutex);
    while(counter < thread_count){
        printf("ESPERANDO \n");
    };

    if(my_rank==0){
        printf("ALL THREADS HAVE REACHED THIS POINT");
        fflush(stdout);
    }
     
        
    return NULL;
}