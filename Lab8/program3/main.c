#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_alarm(int sig) {
}

void setup_alarm(int duration, const char *text) {
    signal(SIGALRM, handle_alarm);
    alarm(duration);
    pause();
    printf("Scheduled Alarm: %s\n", text);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <duration in seconds> <message>\n", argv[0]);
        return 1;
    }

    int duration = atoi(argv[1]);
    char *message = argv[2];

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        setup_alarm(duration, message);
        exit(0);
    } else {
        printf("Alarm set for %d seconds. Child process PID: %d\n", duration, child_pid);
        exit(0);
    }

    return 0;
}
