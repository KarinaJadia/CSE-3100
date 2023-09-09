//#include <stdio.h>
//#include <stdlib.h>

// made a function to do powers
int power(int num, int pow) {
    int n = num;
    while (pow > 1) {
        num = num * n;
        pow --;
    }
    return num;
}

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;

    // my code below
    for (i = 0; i <= n; i++) {
        double sixteeni = power(16, i);

        // catches when raised to the power of 0
        if (i == 0) {
            sixteeni = 1;
        }

        // the math part
        pi = pi + (1.0 / sixteeni) * ((4.0 / (8 * i + 1)) - (2.0 / (8 * i + 4)) - (1.0 / (8 * i + 5)) - (1.0 / (8 * i + 6)));
    }
	

	printf("PI = %.10f\n", pi);
	return 0;
}