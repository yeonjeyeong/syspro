#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void mySignal(int signo, void (*handler)(int)) {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (sigaction(signo, &act, NULL) == -1) {
        perror("sigaction error");
        exit(1);
    }
}
void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}
int main() {
    mySignal(SIGALRM, alarmHandler);
    alarm(5);
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    return 0;
}

