#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void pattern_1(int num_of_processes) {
    for (int i = 0; i < num_of_processes; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("Process %d beginning (PID: %d)\n", i + 1, getpid());
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0) {
            wait(NULL);
            sleep(1);
            printf("Process %d exiting\n", i + 1);
        }
        else {
            printf("Fork failed\n");
        }
    }
}

void pattern_2(int num_of_processes, int count) {
    pid_t pid = fork();

    if (num_of_processes == 1) {
        wait(NULL);
        sleep(1);
        printf("Process %d (%d) exiting\n", count, getpid());
        return;
    }

    if (pid > 0) {
        wait(NULL);
        sleep(1);
        printf("Process %d (%d) exiting\n", count, getpid());
    }
    else if (pid == 0) {
        printf("Process %d (%d) creating Process %d\n", count, getpid(), count + 1);
        pattern_2(num_of_processes - 1, count + 1);
        exit(EXIT_SUCCESS);
    }
    else {
        printf("Fork failed\n");
    }
}

int main(int argc, char* argv[]) {

    int num_of_processes = atoi(argv[1]);
    int pattern_num = atoi(argv[2]);

    if (num_of_processes < 1) {
        printf("Number of processes must be at least 1\n");
    }

    if (pattern_num != 1 && pattern_num != 2) {
        printf("Pattern number must be either 1 or 2\n");
    }
    else {
        if (pattern_num == 1) {
            printf("Running Pattern 1...\n");
            pattern_1(num_of_processes);
        }
        else {
            printf("Running Pattern 2...\n");
            pattern_2(num_of_processes, 1);
        }
    }

    return 0;
}