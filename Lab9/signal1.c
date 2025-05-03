#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// SIGINT handler
void sigint_handler(int signum) {
    fprintf(stdout, "Caught SIGINT signal (%d)\n", signum);
}

// SIGUSR1 handler
void usr1_handler(int signum) {
    fprintf(stdout, "Caught SIGUSR1 signal (%d)\n", signum);
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        return 1;
    }

    // SIGUSR1 handler
    if (signal(SIGUSR1, usr1_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGUSR1!\n");
        return 1;
    }

    printf("Press Ctrl+C to test SIGINT. PID: %d\n", getpid());
    printf("Or run 'kill -SIGUSR1 %d' from another terminal.\n", getpid());

    while (1) {
        sleep(1);  // program runing
    }

    return 0;
}
