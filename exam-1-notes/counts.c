#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void letter_counts(char a[], int n, int counts[26]) {
    for (int i = 0; i < 26; i++) {
        counts[i] = 0; // Initialize all counts to 0
    }

    for (int i = 0; i < n; i++) {
        if (a[i] >= 'a' && a[i] <= 'z') {
            counts[a[i] - 'a']++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);
    printf("n=%d\n", n);
    assert(n >= 1 && n <= 10000);

    char a[n];
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += 2 * i + 1;
        a[i] = sum % 26 + 97;
    }

    int counts[26];
    letter_counts(a, n, counts);

    // Print the counts for each letter
    for (int i = 0; i < 26; i++) {
        if (counts[i] != 0) {
            printf("%c %d\n", i + 'a', counts[i]);
        }
    }

    return 0;
}