//#include <stdio.h>
//#include <stdlib.h>

double two_d_random(int n) {

    int x = (2*n+1); // determines the size of the 2D grid
    int place_x = n; // x-coordinate of the starting point
    int place_y = n; // y-coordinate of the starting point
    int visted[x][x]; // makes an array of grid size to track where visited
    double total_steps = 0.0; // counts total steps taken
    double possible_steps = (2*n-1)*(2*n-1); // total possible steps in the grid

    // initializes the visted array
    for (int i = 0; i < x; i++) {
        for(int j = 0; j < x; j++) {
                visted[i][j] = 0;
            }
        }

    // walks until reaching boundary of grid
    while (place_x > 0 && place_y > 0 && place_x < 2*n && place_y < 2*n) {
        int r = rand() % 4; // generates a random number for direction: 0, 1, 2, or 3
        visted[place_x][place_y] = 1; // marks the current point as visited

         // moves according to the random direction
        if (r == 0) place_y++; // going up
        if (r == 1) place_x++; // going right
        if (r == 2) place_y--; // going down
        if (r == 3) place_x--; // going left
    }
    
    // calculates the fraction of visited points inside the square
    double holder = 0.0;
    for (int i = 0; i < x; i++) {
        for(int j = 0; j < x; j++) {                    
                holder += visted[i][j];
            }
        }
    return holder / possible_steps;
}

//Do not change the code below
int main(int argc, char* argv[]) {
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}
