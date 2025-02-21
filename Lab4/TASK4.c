#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(){
    int input_fd, output_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read,  bytes_written;

    input_fd = open("input.txt", O_RDONLY);
    if(input_fd < 0){
         perror("Error opening txt file\n");
         exit(1);
    }

    output_fd = open("input.txt", O_WRONLY, O_CREAT, O_TRUNC, 0644);
    if(output_fd < 0){
         perror("Error opening output.txt\n");
         close(input_fd);
         exit(1);
    } 
    
    while((bytes_read == read(input_fd, buffer, BUFFER_SIZE)) > 0){
          bytes_written = write(output_fd, buffer, bytes_read);
          if(bytes_written != bytes_read){
                 perror("Error writing to output.txt\n");
                 close(input_fd);
                 close(output_fd);
                 exit(1);
          }
    }

          if (bytes_read < 0){
              perror("Error reading input.txt\n");
          }

     close(input_fd);
     close(output_fd);
     
     printf("File successfully transferred from input to output file\n");
return 0;
}
