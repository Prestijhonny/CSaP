// Create a program that forks, waits for its child to successfully print a message
// to the screen, and prints another message before exiting
//  ----------------------------------------------------------
//  Modify the previous program so that a given number of children
//  are generated on the command line. What happens to the other children?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int numProc = atoi(argv[1]);
    pid_t pid[numProc];
    int state;
    for (int i = 0; i < numProc; i++)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            // Child
            printf("I'm child process %d with pid %d\n", i + 1, getpid());
            exit(0);
        }
        else if (pid[i] < 0)
        {
            // Error case
            printf("Fork error\n");
            exit(-1);
        }
    }

    for (int i = 0; i < numProc; i++)
    {
        if (pid[i] > 0)
        {
            // Parent
            wait(&state);
            printf("I'm father process with pid %d, the child process %d ended with code %d\n", getpid(),i+1, state);
        }
    }
}