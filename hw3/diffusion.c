//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n) {
    int random;
    int x = 0, y = 0, z = 0; // tracks positions

    for(int i = 0; i < n; i++) { // loop simulates movement n times
        random = rand() % 6;

        if(random == 0) x--;
        else if(random == 1) x++;
        else if(random == 2) y++;
        else if(random == 3) y--;
        else if(random == 4) z++;
        else if(random == 5) z--;
    }

    z = z + ((2*n+1)/2);
    y = y + ((2*n+1)/2);
    x = x + ((2*n+1)/2);

    x = x * (2*n+1) * (2*n+1);
    y = y * (2*n+1);
    int idx = x + y + z;
    grid[idx]+=1;
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r) {
    int x = 0, y = 0, z = 0; // tracks starting positions
    int index;
    double c1 = 0, c2 = 0; // counters
    for(int i = 0; i < (2*n+1) * (2*n+1) * (2*n+1); i++) {
        index=i;
        while(index - ((2*n+1) * (2*n+1)) >= 0) {
            x++;
            index -= (2*n+1) * (2*n+1);
        }
        while(index - (2*n+1) >= 0) {
            y++;
            index-=(2*n+1);
        }
        while(index - 1 >= 0) {
            z++;
            index -= 1;
        }
        x-=n;
        y-=n;
        z-=n;
        if (abs(x) * abs(x) + abs(y) * abs(y) + abs(z) * abs(z) <= (r*n) * (r*n)) {
            c1 += grid[i];
        }
        c2 += grid[i];
        x = 0;
        y = 0;
        z = 0;
    }
    return c1/c2;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++) {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
    int * grid = calloc((2*n+1)*(2*n+1)*(2*n+1),sizeof(int)); // my code

	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);

	//fill in some code below
    free(grid); // my code
}

int main(int argc, char *argv[]) {
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}