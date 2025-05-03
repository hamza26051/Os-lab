#define _XOPEN_SOURCE 700  // Ensure POSIX compliance
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT
void sigint_handler(int signum) {
    printf("Ctrl+C (SIGINT) received. Exiting...\n");
    exit(signum);  // Terminate with status = signal number (2)
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;  // Assign handler
    sigemptyset(&sa.sa_mask);        // Clear blocked signals during handler
    sa.sa_flags = SA_RESTART;        // Restart interrupted system calls

    // Register SIGINT handler using sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Press Ctrl+C to test SIGINT (PID: %d)\n", getpid());
    while (1) {
        sleep(1);  // Keep program running
    }
    return EXIT_SUCCESS;
}
