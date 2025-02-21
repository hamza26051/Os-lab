#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
     pid_t pid = fork();
     
    if(pid < 0){
       perror("Fork failed");
       exit(1);
    }
    else if(pid == 0){
       printf("Child process executing 'ls'\n");
       execlp("ls", "ls", NULL);

       perror("Excelp failed\n");
       exit(1);
    }
    else{
       wait(NULL);
       printf("Parent process: Child process has completed\n");
    }

return 0;
}
