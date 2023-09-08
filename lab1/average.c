#include <stdio.h>
int main(void)
{
        
    double x,total,average,c;
    c = 1;

    while (scanf("%lf", &x) == 1) {

        total=total+x;
                
        average= total/c;
        c++;
        printf("Total=%f Average=%f\n", total, average);
    }
}