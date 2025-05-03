
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;
sem_t mutex, wrt;

void* reader(void* arg) {
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %ld is reading\n", (long)arg);
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}

void* writer(void* arg) {
    while (1) {
        sem_wait(&wrt);

        printf("Writer %ld is writing\n", (long)arg);
        sleep(1);

        sem_post(&wrt);
        sleep(1);
    }
}

int main() {
    pthread_t r[3], w[2];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (long i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, (void*)i);
    for (long i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, (void*)i);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    return 0;
}
