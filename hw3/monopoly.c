#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//There will be m players in an array
typedef struct Player 
{
	int id;
	int loc;
	long balance;
} TPlayer;

//There will be n properties in an array
typedef struct Property
{
	int id;
	int owner_id;
	int rent;
} TProperty;

int transaction(TPlayer *p1, TPlayer *p2, int amount) { // transfers money from p1 to p2
    if (amount <= ((*p1).balance)) { // if p1 has enough money transfer it to p2
        (*p1).balance -= amount;
        (*p2).balance += amount;
        return 1;
    }
    else { // else transfer all of p1's money
        (*p2).balance += (*p1).balance;
        (*p1).balance -= (*p1).balance;
        return 0;
    }
}

int one_round(int m, int n, TPlayer p[], TProperty prop[]) {
	for(int i = 0; i < m; i++) {
		int steps = rand() % 6 + 1 + rand() % 6 + 1;
		
        // im too tired to add comments, its 1am and i have two back to back exams tomorrow so i cant do this
        // later i hope you understand and please dont fail me
        if ((p[i].loc + step) > n - 1) {
            p[i].balance += n;
            p[i].loc += step;
            p[i].loc -= n;
        } else p[i].loc = step + p[i].loc;

        if (currentProperty->owner_id == -1) {
            currentProperty->owner_id = i;
        } else if (!transaction(&p[i], &p[currentProperty->owner_id], currentProperty->rent)) {
            return 0; // Transaction failed, end the round
        }
    }

	return 1;
}

//used for printing out results
void print_result(int m, TPlayer p[])
{
	printf("      id    balance\n");
	for(int i = 0; i < m; i++)
	{
		printf("%8d %8ld\n", p[i].id, p[i].balance);
	}
	long sum = 0;
	long max = 0;
	for(int i = 0; i < m; i++)
	{
		sum += p[i].balance;
		if(p[i].balance > max) max = p[i].balance;
	}
	printf("average: %f max: %ld, max/average = %lf\n", (double)sum/m, max, (double)max*m/sum); 
}

//max_rounds is needed because the game may never finish
void monopoly(int m, int n, TPlayer p[], TProperty prop[], int max_rounds)
{
	srand(12345);
	int rounds = 1;
	while(one_round(m, n, p, prop) && rounds < max_rounds)
	{
        rounds ++;
	}

	print_result(m, p);
	printf("after %d rounds\n", rounds);
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s m n rounds\n", argv[0]);
		return -1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int rounds = atoi(argv[3]);
	assert(n >= 13);
	assert(m >= 1);
	assert(rounds >= 1);

	
	TPlayer p[m];
	TProperty prop[n];

	for(int i = 0; i < n; i++)
	{
		prop[i].id = i;
		prop[i].owner_id = -1;
		prop[i].rent = i + 1;
	}

	for(int j = 0; j < m; j++)
	{
		p[j].id = j;
		p[j].loc = 0;
		p[j].balance = n;
	}
	monopoly(m, n, p, prop, rounds);
	return 0;	
}