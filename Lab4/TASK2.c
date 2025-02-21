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
          for (int i=0; i<100; i++){
               printf("I am a child process\n");
               usleep(10000);
          }
          exit(0);
     }
     else{
          for(int i=0; i<100; i++){
                printf("I am a parent process\n");
                usleep(10000);
          }
          wait(NULL);
     }
     
     return 0;
}
