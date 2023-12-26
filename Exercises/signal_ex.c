// Captures user-defined signals (SIGUSR1, SIGUSR2) and prints a reception message
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sigCode);

int main ()
{
    signal(SIGUSR1,handler);
    while(1);
    exit(0);
}


void handler ( int sigCode)
{
    printf("Received SIGUSR1 %d\n",sigCode);
}