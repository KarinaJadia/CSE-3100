#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100000

//Return the next index and update a[]
/*In this problem we will write a program to simulate a circular walker. A walker walks along the index of
an array in a circular manner. The size of the array is n. The index of the array therefore is between 0 and
n−1. When the walker is at the index k, he will go to index k+a[k] for the next step, if k+a[k] is between 0
and n−1. Otherwise, the modular operation is used to ensure the result is between 0 and n−1. Before the walk
leaves the current index k, the value a[k] is decremented by 1. For example, when k=2, and n=5, if a[k]=4,
then k+a[k]=2+4=6. Applying modular operation we have 6%n=6%5=1. Hence the next index is 1. Before the walker
goes to index 1, a[2] is decremented by 1, and hence a[2] becomes 3. Note if a[k] is 0, the walker will stop.*/
int next_index(int a[], int k, int n) {
    if (a[k] == 0) return k;
    int next_k = (k + a[k]) % n;
    a[k] -= 1;
    return next_k;
}

int main(int argc, char *argv[])
{

	if(argc!=2)
	{
		printf("Usage: %s n\n", argv[0]);
		return -1;
	}
	int a[MAX];

	int n = atoi(argv[1]);
	assert(n >= 1 && n <= MAX);
	for(int i=0; i<n; i++)
	{
		a[i] = i + 1;
	}	

	int k = 0;
	while(a[k] > 0)
	{
		printf("k=%d a[%d] = %d\n", k, k, a[k]);
		k = next_index(a, k, n);
	}
	printf("finally:\nk=%d a[%d] = %d\n", k, k, a[k]);
	return 0;
}