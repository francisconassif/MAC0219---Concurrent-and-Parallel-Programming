#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define QUEUE_SIZE 10
int queue[QUEUE_SIZE];
int front = 0, rear = 0;

void* producer_thread(void* arg){
    for(int i = 0; i < 20; i++){
        if((rear + 1) % QUEUE_SIZE == front){
            printf("Fila cheia!\n");
        }
        else{
            queue[rear] = i;
            rear = (rear+1)%QUEUE_SIZE;
        }
        usleep(7); 
    }
    return NULL;
}

void* consumer_thread(void* arg){
    for(int i = 0; i < 50; i++){
        if(front == rear){
            printf("Fila vazia!\n");
        }
        else{
            int item = queue[front];
            front = (front+1)%QUEUE_SIZE;
            printf("Valor consumido: %d\n", item);
        }
        usleep(73); 
    }
    return NULL;
}

int main(){
    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}
