#include <stdio.h>

int main() {
    FILE *file;
    char fileName[] = "example.txt";

    // Open a file for writing (creates a new file or overwrites an existing one)
    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // Write a character to the file
    fputc('H', file);

    // Write a string to the file
    fputs("ello, World!\n", file);

    // Close the file
    fclose(file);

    // Open the same file for reading
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read and print a character from the file
    int character = fgetc(file);
    putchar(character);

    // Read and print a string from the file
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    printf("%s", buffer);

    // Close the file
    fclose(file);

    return 0;
}
