#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child;
    int exitStatus;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }
    
    if ((child = fork()) == -1) {
        perror("fork()");
        exit(1);
    }
    if (child == 0) {
        execlp(argv[1], argv[1], argv[2], NULL);
        
        perror("execlp()");
        exit(1);
    }
    else {
        wait(&exitStatus);
        if (WIFEXITED(exitStatus)) printf("exited=%d exitstatus=%d\n", child, WEXITSTATUS(exitStatus));
    }
    if ((child = fork()) == -1) {
        perror("fork()");
        exit(1);
    }
    if (child == 0) {
        execvp(argv[3], &argv[3]);

        perror("execvp()");
        exit(1);
    }
    else {
        wait(&exitStatus);

        if (WIFEXITED(exitStatus)) printf("exited=%d exitstatus=%d\n", child, WEXITSTATUS(exitStatus));
    }
    return 0;
}