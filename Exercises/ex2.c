//Create a program that forks, waits for its child to successfully print a message 
//to the screen, and prints another message before exiting

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int state; 
    pid = fork();
    if (pid == 0){
        // Child
        printf("I'm child process with pid %d\n", getpid());
        exit(0);
    }else if(pid > 0){ 
        // Father
        wait(&state);
        printf("I'm father process with pid %d, the child process ended with code %d\n", getpid(), state);
        exit(0);
    }else{
        //Error case
        printf("Fork error\n");
        exit(-1);
    }

}