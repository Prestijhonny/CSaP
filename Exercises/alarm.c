// Example of alarm
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sigCode);


int main()
{
    // Create a signal of type SIGALRM
    signal(SIGALRM, handler);
    // Set an alarm of 3 seconds 
    alarm (3);
    // Since alarm is a non-blocking syscall, i call pause() 
    // so that the calling process can transition to blocked status
    pause();
    exit(0);
}

void handler(int sigCode)
{
    printf("SIGALRM handled %d\n", sigCode);
    
}