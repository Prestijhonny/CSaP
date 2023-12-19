//Create a signal

#include <stdlib.h>
#include <stdio.h>
#include <signal.h> 
#include <unistd.h>

void handler(int value){
    printf("Hi i'm a signal!\n");
    printf("Caught signal %d\n", value);
}

int main()
{
    if (signal(SIGUSR1, handler) == SIG_ERR){
        printf("Error to create a signal\n");
    }
    kill(getpid(),SIGUSR1);

    exit(0);
}

// gcc ex3.c -o ex3;./ex3