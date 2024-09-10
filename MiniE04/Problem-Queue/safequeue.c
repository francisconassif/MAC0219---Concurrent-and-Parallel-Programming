#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define QUEUE_SIZE 10
int queue[QUEUE_SIZE];
int front = 0, rear = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_slots; 
sem_t full_slots;  

void* producer_thread(void* arg){
    for (int i = 0; i < 20; i++){
        sem_wait(&empty_slots);  
        pthread_mutex_lock(&mutex);  
        if ((rear + 1) % QUEUE_SIZE == front){
            printf("Fila cheia!\n");
        }
        else{
            queue[rear] = i;
            rear = (rear+1)%QUEUE_SIZE;
        }
        pthread_mutex_unlock(&mutex); 
        sem_post(&full_slots); 
        usleep(10);
    }
    return NULL;
}

void* consumer_thread(void* arg){
    for(int i = 0; i < 20; i++){
        sem_wait(&full_slots); 
        pthread_mutex_lock(&mutex);  
        if (front == rear){
            printf("Fila vazia!\n");
        }
        else{
            int item = queue[front];
            front = (front + 1) % QUEUE_SIZE;
            printf("Valor consumido: %d\n", item);
        }
        pthread_mutex_unlock(&mutex);  
        sem_post(&empty_slots);  
        usleep(15);
    }
    return NULL;
}

int main(){
    pthread_t producer, consumer;

    sem_init(&empty_slots, 0, QUEUE_SIZE); 
    sem_init(&full_slots, 0, 0);  

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
