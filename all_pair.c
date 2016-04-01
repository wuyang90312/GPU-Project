#include "all_pair.h"

// Assume the number of planets are 10
#define     NUM     10

int main()
{
    // Declare the pointer and allocate the memory
    Body* galaxy, *galaxy_for_all_pair;
	int i;
    galaxy = (Body*)malloc(sizeof(Body)*NUM);
	galaxy_for_all_pair = (Body*)malloc(sizeof(Body)*NUM);

    // read data from csv file
    if(read_csv(galaxy))
        return FALSE;   // if the function fail, return false
		
	if(read_csv(galaxy_for_all_pair))
        return FALSE;   
    printf("The size of galaxy is %p <= %lf\n", (void*)&galaxy[0], galaxy[5].posX);
    
    //Barnes_Hut(galaxy, NUM);
	All_Pair(galaxy_for_all_pair, NUM);
	printf("From All Pair Calculation: \n");
	for (i = 0; i < NUM; i++)
		printf("Star %d has resulting force: %f\n", i, sqrt(pow((double)galaxy_for_all_pair[i].forceX, 2) + pow((double)galaxy_for_all_pair[i].forceY, 2)));
    return TRUE;
}

int All_Pair(Body* galaxy, int size){

	int i, j;
	double result[2];
	for (i = 0; i < size; i++){
		galaxy[i].forceX = 0;
		galaxy[i].forceY = 0;
		for (j = 0; j < size; j++){
			if (i != j){
				if(cal_force(galaxy[i], galaxy[j],  result) == 0){
					galaxy[i].forceX += result[0];
					galaxy[i].forceY += result[1];
				}
			}
		
		}
		printf("**********force %d : %f\n", i, sqrt(pow((double)galaxy[i].forceX, 2) + pow((double)galaxy[i].forceY, 2)));
	}
}

