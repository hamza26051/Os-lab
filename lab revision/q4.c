#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CUSTOMERS 5

sem_t chefs;
pthread_mutex_t order_lock;
int order_id = 1;

void *customer(void *arg) {
    pthread_mutex_lock(&order_lock);
    int my_order = order_id++;
    printf("Customer %ld placed order %d\n", (long)arg, my_order);
    pthread_mutex_unlock(&order_lock);

    sem_wait(&chefs);
    printf("Chef is preparing order %d for customer %ld\n", my_order, (long)arg);
    sleep(2);
    printf("Chef finished order %d for customer %ld\n", my_order, (long)arg);
    sem_post(&chefs);
    pthread_exit(NULL);
}

int main() {
    pthread_t customers[NUM_CUSTOMERS];
    sem_init(&chefs, 0, 2);
    pthread_mutex_init(&order_lock, NULL);

    for (long i = 0; i < NUM_CUSTOMERS; i++)
        pthread_create(&customers[i], NULL, customer, (void *)i);

    for (int i = 0; i < NUM_CUSTOMERS; i++)
        pthread_join(customers[i], NULL);

    sem_destroy(&chefs);
    pthread_mutex_destroy(&order_lock);
    return 0;
}
