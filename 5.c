#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <limits.h>

int main() {
    // a. Maximum length of the arguments to the exec family of functions
    printf("Maximum length of arguments to exec: %ld\n", sysconf(_SC_ARG_MAX));

    // b. Maximum number of simultaneous processes per user ID
    printf("Maximum number of simultaneous processes per user ID: %d\n", _SC_OPEN_MAX);

    // c. Number of clock ticks (jiffy) per second
    printf("Number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));

    // d. Maximum number of open files
    printf("Maximum number of open files: %d\n", _SC_OPEN_MAX);

    // e. Size of a page
    printf("Size of a page: %ld bytes\n", sysconf(_SC_PAGESIZE));

    // f. Total number of pages in the physical memory
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("Total number of pages in physical memory: %ld\n", info.totalram / sysconf(_SC_PAGESIZE));
    } else {
        perror("sysinfo");
    }

    // g. Number of currently available pages in the physical memory
    printf("Number of currently available pages in physical memory: %ld\n", info.freeram / sysconf(_SC_PAGESIZE));

    return 0;
}
