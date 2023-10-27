int main() {
    pid_t value; // initializes value of process ID (which tells you which process you're in)
    int status;

    value = fork(); // creates the fork, so now the program has been cloned

    if (value < 0) perror("fork failed"), exit(1); // if value < 0, that means fork failed

    if (value == 0) printf("in child\n"), exit(0); // if value = 0, that means in child process

    else {
        printf("in parent, waiting for child to finish\n");

        if (waitpid(value, &status, 0) == -1) perror("wait failed"), exit(1); // wait for child to complete and check status
            // this is also where status gets updated
        
        if (WIFEXIT(status)) printf("child exit status: %d\n", WEXITSTATUS(status)); // check if child was terminated normally

        printf("parent is done\n");
    }

    return 0;
}