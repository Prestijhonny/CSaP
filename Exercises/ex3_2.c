// Intercepts SIGCHILD for each child that you create (NUMCHLD) from parent process and for each of them print a warning message with their PID. Upon termination of all children, the parent has to print a warning message followed by the list of their PIDs and exit statuses and finally exits

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#define NUMCHLD 5


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
        if ((pids[i] = fork()) == 0)
        {
            // Childen code
            printf("I'm child process with PID %d\n", getpid());
            srand(time(NULL) + getpid());
            exit(rand());
        }
        else if (pids[i] == -1)
        {
            // Error
            printf("Error to create process %d\n", pids[i]);
            exit(-1);
        }
    }

    // Parent code
    int j =0;
    for (j = 0; j < NUMCHLD; j++)
    {
        wait(&stato[j]);
        if (stato[j] >= 256){
            // Voluntary exit, the leftmost bit are filled by the exit code of child process
            printf("Warning message: child process with PID %d and exit status %d\n", pids[j], stato[j] >> 8);
        }else{
            // Forced exit, the rightmost bit are filled by the signal code of child process
            printf("Forced exit: child process with PID %d exit with signal code %d\n", pids[j], stato[j]);
        }
    }

    exit(0);
}