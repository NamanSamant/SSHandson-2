#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    struct timespec start, end;
    long long elapsed_time;
    pid_t pid;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 100; i++) {
        pid = getppid();
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Time taken to execute 100 getppid() system calls: %lld nanoseconds\n", elapsed_time);

    return 0;
}
