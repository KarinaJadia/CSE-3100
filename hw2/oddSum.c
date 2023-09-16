//#include <stdio.h>
//#include <stdlib.h>

int oddSumHelp(int count, int bound, int value) {
    // this is for me to remember what the variables are because im stupid
    // also do you read comments?
    // peepee poopoo

    // count = how many odd integers should be included in the sum
    // bound = largest integer in the solution allowed
    // value = the target sum that you want to achieve with the series of odd integers
    
    if (count == 0 && value == 0) return 1; // if both count and value are zero, we have found a solution
    if (count <= 0) return 0; // if count is zero or negative, no solution can be found    
    if (bound <= 0) return 0; // if bound is zero or negative, no solution can be found
    if (value < 0) return 0; // if value is negative, no solution can be found

    // recursively calls oddSumHelp with subtracted count, bound, and updated value
    if (oddSumHelp(count - 1, bound - 2, value - bound) == 1) {
        // if solution is found, print the current 'bound' value and return 1 to indicate success
        printf("%i ",bound);
        return 1;
    }
    else {
        // if no solution is found with the current bound, try the next bound value
        oddSumHelp(count, bound - 2, value);
    }
}

//Do not change the code below
void oddSum(int count, int bound, int value)
{
    	if(value <= 0 || count <= 0 || bound <= 0) return;
    
    	if(bound % 2 == 0) bound -= 1;

    	if(!oddSumHelp(count, bound, value)) printf("No solutions.\n");
	else printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc != 4) return -1;

	int count = atoi(argv[1]);
	int bound = atoi(argv[2]);
	int value = atoi(argv[3]);

	//oddSum(12,30,200);
	//oddSum(10,20,100);
	//oddSum(20,20,200);
	oddSum(count, bound, value);
	return 0;
}