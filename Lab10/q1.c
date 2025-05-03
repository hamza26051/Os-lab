#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}

int main() {
    pthread_t prod[NUM_PRODUCERS], cons[NUM_CONSUMERS];

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_create(&prod[i], NULL, producer, NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_create(&cons[i], NULL, consumer, NULL);

    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(prod[i], NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(cons[i], NULL);

    return 0;
}
