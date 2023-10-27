#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int main() {
    pid_t value; // initializes value of process ID (which tells you which process you're in)

    value = fork(); // creates the fork, so now the program has been cloned

    if (value < 0) perror("fork failed"), exit(1); // if value < 0, that means fork failed

    if (value == 0) { // entered child and created an infinite loop to demonstrate

        printf("in child\n");
        int n = 0;
        while (1) {
            n++;
        }
    }

    else { // entered parent

        printf("in parent\n");

        if (kill(value, SIGTERM) == -1) perror("kill failed"), exit(1); // send SIGTERM (termination) to child
            // generally sigterm is automatically defined and represents the termination signal

        int status;
        if (waitpid(value, &status, 0) == -1) perror("wait failed"), exit(1); // wait for child to complete and check status
            // this is also where status gets updated

        if (WIFSIGNALED(status)) printf("child process terminated by signal %d\n", WTERMSIG(status)); // if kill succesful

        printf("parent done\n");
    }

    return 0;
}