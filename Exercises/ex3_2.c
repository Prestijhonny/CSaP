// Intercepts SIGCHILD for each child that you create (NUMCHLD) from parent process and for each of them print a warning message with their PID. Upon termination of all children, the parent has to print a warning message followed by the list of their PIDs and exit statuses and finally exits

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define NUMCHLD 5

static int exitCode = 0;

void handler(int sigVal)
{
    printf("Warning handler: caught signal SIGCHLD %d\n", sigVal);
}

int main()
{
    int i = 0;
    pid_t pids[NUMCHLD];
    int stato[NUMCHLD] = {0};
    if (signal(SIGCHLD, handler) == SIG_ERR)
        printf("Error to create a signal\n");
    for (i = 0; i < NUMCHLD; i++)
    {
        // ++exitCode;
        if ((pids[i] = fork()) == 0)
        {
            // Childen code
            printf("I'm child process with PID %d\n", getpid());
            exit(123);
        }
        else if (pids[i] == -1)
        {
            // Error
            printf("Error to create process %d\n", pids[i]);
            exit(-1);
        }
    }

    // Parent code
    for (int j = 0; j < NUMCHLD; j++)
    {
        wait(&stato[j]);
        printf("Warning message: child process with PID %d and exit status %d\n", pids[j], stato[j] >> 8);
    }

    exit(0);
}