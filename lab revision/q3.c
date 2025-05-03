#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int account_balance = 1000;
pthread_mutex_t lock;

void *teller(void *id) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        int amount = rand() % 200 - 100;
        account_balance += amount;
        printf("Teller %ld updated balance by %d. New balance: %d\n",
               (long)id, amount, account_balance);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tellers[3];
    pthread_mutex_init(&lock, NULL);

    for (long i = 0; i < 3; i++)
        pthread_create(&tellers[i], NULL, teller, (void *)i);

    for (int i = 0; i < 3; i++)
        pthread_join(tellers[i], NULL);

    pthread_mutex_destroy(&lock);
    printf("Final account balance: %d\n", account_balance);
    return 0;
}
