// Unamed PIPE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
    int fd[2];
    if (pipe(fd)){
        printf("Error to create a PIPE.\n");
        exit(-1);
    }
    pid_t pid = fork();
    char in[] = "Hello i'm father process!\n";
    char out[24];
    switch (pid)
    {
    case 0:
        // Child code
        // Close write descriptor for child process
        close(fd[1]);
        read(fd[0],out, sizeof(out));
        printf("I'm child process and i've read from pipe:\n%s\n",out);
        exit(0);
        break;
    case -1:
        // Error 
        printf("Fork error!\n");
        exit(-1);
        break;
    default:
        // Parent code
        // Close read descriptor for parent process
        close(fd[0]);
        printf("I'm parent process and i'm writing on pipe...\n");
        write(fd[1],in,strlen(in));
        wait(NULL);
        break;
    }
    exit(0);
}