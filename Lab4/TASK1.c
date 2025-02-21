#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid1, pid2;
    pid1 = fork();
    if(pid1<0){
        perror("Fork failed");
        exit(1);
    }
    else if(pid1 == 0){
        printf("First child process  - PID: %d\n", getpid());
        exit(0);
    }
    else{
        pid2 = fork();
        if(pid2 < 0){
            perror("Fork failed");
            exit(1);
        }
        else if(pid2 == 0){
            printf("Second child process - PID: %d\n", getppid());
            exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
    printf("Parent process exiting - PID: %d\n", getpid());
    return 0;
}
