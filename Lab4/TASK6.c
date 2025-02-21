#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_alarm(int sig){
         printf("Alarm received! Program will terminate now\n");
         exit(0);
}

int main(){
      signal(SIGALRM, handle_alarm);

      alarm(5);
      printf("Alarm sent for 5 sec. Printed every sec\n");
      
      while(1){
           printf("Program running\n");
           sleep(1);
      }
return 0;
}
