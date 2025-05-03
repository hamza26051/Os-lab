#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void sigusr1_handler(int signo) {
    printf("Thread %lu received SIGUSR1\n", pthread_self());
}

void* worker(void* arg) {
    // To install handler per-thread instead of in main():
    // signal(SIGUSR1, sigusr1_handler);

    printf("Thread %lu: started, waiting for signal…\n", pthread_self());
    pause();
    printf("Thread %lu: exiting\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t th[3];

    /* Install handler process-wide */
    signal(SIGUSR1, sigusr1_handler);

    /* Spawn three worker threads */
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&th[i], NULL, worker, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    sleep(1);  // let threads reach pause()

    /* 1) Signal the whole process */
    printf("Main: sending SIGUSR1 to process\n");
    kill(getpid(), SIGUSR1);
    sleep(1);

    /* 2) Signal only the third thread */
    printf("Main: sending SIGUSR1 to thread %lu only\n", th[2]);
    pthread_kill(th[2], SIGUSR1);
    sleep(1);

    return 0;
}
