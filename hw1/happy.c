//#include <stdio.h>
//#include <stdlib.h>

int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	int m = n;
	
    // my code below
    while (n != 1 && n != 4) {
        int n1,n2 = 0,n3 = 0;
        n1 = n % 10; // this is the ones place
        n2 = n % 100; // this is the tens place
        n2 = n2 / 10; // still the tens place
        n3 = n/100; // this is the hundreds place 
        
        n = n1 * n1 + n2 * n2 + n3 * n3;
        printf("%d\n",n);
    }

	if(n==1) printf("%d is a happy number.\n", m);
	else printf("%d is NOT a happy number.\n", m);
	return 0;
}