#include <stdio.h> 

int main(void) { 
    printf("Hello, World!\n");

    int a = 0;
    int total = 0;
    while (a < 200) {
        total += a;
        a += 2;
    }

    printf("total: %d\n", total);

    return 0;
}