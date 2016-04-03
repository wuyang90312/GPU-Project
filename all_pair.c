#include "all_pair.h"

// Assume the number of planets are 10
#define     NUM     10000

int main()
{
    clock_t  start, stop;
	float elapsedTime;// define time to calcualte the average duration
    // Declare the pointer and allocate the memory
    Body *galaxy_for_all_pair;
	int i;
	galaxy_for_all_pair = (Body*)malloc(sizeof(Body)*NUM);
		
	if(read_csv(galaxy_for_all_pair))
        return FALSE;   
    printf("The size of galaxy is %p <= %lf\n", (void*)&galaxy_for_all_pair[0], galaxy_for_all_pair[5].posX);
    
    //Barnes_Hut(galaxy, NUM);
    start = clock();
	All_Pair(galaxy_for_all_pair, NUM);
    stop = clock();
    elapsedTime = (float) (stop - start)/ CLOCKS_PER_SEC;
    printf("Barnes-Hut time: %lf s\n", elapsedTime);
	//printf("From All Pair Calculation: \n");
	/*for (i = 0; i < NUM; i++)
		printf("Star %d has resulting force: %f\n", i, sqrt(pow((double)galaxy_for_all_pair[i].forceX, 2) + pow((double)galaxy_for_all_pair[i].forceY, 2)));*/
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
			    cal_force(galaxy[i], galaxy[j],  result);
				galaxy[i].forceX += result[0];
				galaxy[i].forceY += result[1];
			}
		
		}
		//printf("**********force %d : (%f, %f) \n", i, galaxy[i].forceX, galaxy[i].forceY);
	}
}

