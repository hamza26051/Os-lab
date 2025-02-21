#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
     pid_t pid = fork();
     if(pid < 0){
         perror("Fork failed\n");
         exit(1);
     }
     else if(pid == 0){
         printf("Child process executing 'ls - l'\n");
         execlp("ls", "ls", "-l", NULL);

         perror("Excelp failed\n");
         exit(1);
     }

     else{
        wait(NULL);
        printf("Parent Process: Child process has completed\n");
     }

return 0;
}
