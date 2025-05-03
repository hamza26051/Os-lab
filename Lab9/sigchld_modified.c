#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>

void proc_exit() {
    int wstat;
    pid_t pid;
    while (1) {
        pid = wait3(&wstat, WNOHANG, NULL);
        if (pid == 0 || pid == -1) {
            fprintf(stdout, "return value of wait3() is %d\n", pid);
            return;
        }
        fprintf(stdout, "Child %d exited with code: %d\n",
                pid, WEXITSTATUS(wstat));
    }
}

int main() {
    signal(SIGCHLD, proc_exit);

    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            // Child process
            printf("Child %d: I'm alive (temporarily)\n", getpid());
            int ret_code = rand() % 100;
            printf("Child %d: Return code is %d\n", getpid(), ret_code);
            exit(ret_code);
        }
    }

    // Parent process sleeps to let children become zombies briefly
    printf("Parent %d sleeping for 5 seconds...\n", getpid());
    sleep(5);
    printf("Parent exiting.\n");
    return 0;
}
