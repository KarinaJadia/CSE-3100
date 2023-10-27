#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>

//redirect standard input to the specified file
void redirectStdin(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if(fd < 0)
    {
        perror("Error opening the file\n");
        exit(-1);
    }
	//TODO
    //fill in the code below
    if (dup2(fd, STDIN_FILENO) == -1) perror("redirect error\n"), exit(-1);
    close(fd);

}

//redirect standad output to the specified file
void redirectStdout(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd < 0)
    {
        perror("Error opening the file\n");
        exit(-1);
    }
	//TODO
	//fill in the code below
    if (dup2(fd, STDOUT_FILENO) == -1) perror("redirect error\n"), exit(-1);
    close(fd);
}

//TODO: imeplement the following function
int increasing(char *word)
{
    if(strlen(word)<5) return 0;
    //TODO
    if (strlen(word) < 2) return 1; // if this it's one letter long, that's alphabetical
    for (int j = 0; word[j] != '\0' && word[j + 1] != '\0'; j++) { // goes through each letter
        if (word[j + 1] < word[j]) return 0; // alphabetical order is same as numerical order
    }
    return 1;
}