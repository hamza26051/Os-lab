
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopsticks[N];

void* philosopher(void* num) {
    int id = (int)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3);

        pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&chopsticks[(id + 1) % N]);
        pthread_mutex_unlock(&chopsticks[id]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopsticks[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
