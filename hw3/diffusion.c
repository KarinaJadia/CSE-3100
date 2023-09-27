//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>

void one_particle(int *grid, int n) { // calculates the position of one particle after n moves and updates
// its final position on the grid

    int random;
    int x = 0, y = 0, z = 0; // tracks positions
    int gs = 2*n+1; // dimension spans from -n to n so total number of possible positions along the grid
    // is (2*n+1) so that's the grid size

    // loop simulates movement n times
    for(int i = 0; i < n; i++) {
        random = rand() % 6;

        // moves it in the direction based on whatever the direction is
        if(random == 0) x--;
        else if(random == 1) x++;
        else if(random == 2) y++;
        else if(random == 3) y--;
        else if(random == 4) z++;
        else if(random == 5) z--;
    }

    // adding it to grid size divided by 2 to make sure that the coordinates are adjusted to map correctly
    // to the middle of the grid
    z = z + (gs/2);
    y = y + (gs/2);
    x = x + (gs/2);

    // doing so to adjust the 3D measurements so it can be compressed into a 1D measurement
    x = x * gs * gs;
    y = y * gs;

    int pos = x + y + z; // the value of the final calculated position of the particle
    grid[pos] += 1; // updates grid to say that that position has been visited one (more) time
}

double density(int *grid, int n, double r) { // returns the proportion of particles in the grid that are
// within the sphere of rn radius from the origin

    int x = 0, y = 0, z = 0; // initializes positions
    int index; // stores current index in grid
    double c1 = 0, c2 = 0; // counters for particles in sphere and particles total
    int gs = 2*n+1; // i refuse to keep typing it out

    // goes over every position in grid
    for(int i = 0; i < gs * gs * gs; i++) {
        index = i;

        // calculates x, y, and z coordinates based on current index
        while(index - (gs * gs) >= 0) { x++; index -= gs * gs; }
        while(index - gs >= 0) {y++; index -= gs; }
        while(index - 1 >= 0) { z++; index -= 1; }

        // adjusts x, y, and z to correctly map in grid
        x -= n;
        y -= n;
        z -= n;

        // in order to avoid square rooting, i squared the other side
        if (abs(x) * abs(x) + abs(y) * abs(y) + abs(z) * abs(z) <= (r*n) * (r*n)) {
            c1 += grid[i]; // if particle in sphere, add particle(s) in that location
        }
        c2 += grid[i]; // add particle(s) in that location
        x = 0; y = 0; z = 0; // resets positions
    }

    return c1/c2; // returns proportion of particles in sphere to total
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++) {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

void diffusion(int n, int m) { // allocates memory to make grid, makes grid, prints grid, and then frees
// memory allocation

    int * grid = calloc((2*n+1)*(2*n+1)*(2*n+1),sizeof(int)); // added, allocates memory for proper-sized grid
	for(int i = 1; i<=m; i++) one_particle(grid, n); // simulates movement of m particles
	print_result(grid, n); // peepee poopoo
    free(grid); // added, frees memory
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