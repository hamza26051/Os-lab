#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void print_user_id(){
     uid_t uid = getuid();
     printf("UserID: %d\n", uid);
}
int main(){
     pid_t pid = getpid();
     pid_t ppid = getppid();

     printf("Child process id is: %d\n",pid);
     printf("Parent process id is: %d\n",ppid);

     print_user_id();

     return 0;
}
