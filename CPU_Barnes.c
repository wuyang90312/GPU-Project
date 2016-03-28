#include "CPU_Barnes.h"

// Assume the number of planets are 10
#define     num     10

int main()
{
    // Declare the pointer and allocate the memory
    Body* galaxy, *galaxy_for_all_pair;
	int i;
    galaxy = (Body*)malloc(sizeof(Body)*num);
	

    // read data from csv file
    if(read_csv(galaxy))
        return FALSE;   // if the function fail, return false
		
	if(read_csv(galaxy_for_all_pair))
        return FALSE;   
    printf("The size of galaxy is %p <= %lf\n", (void*)&galaxy[0], galaxy[5].posX);
    
    Barnes_Hut(galaxy, num);
	All_Pair(galaxy_for_all_pair, num);
	printf("From All Pair Calculation: \n");
	for (i = 0; i < num; i++)
		printf("Star %d has resulting force: %f\n", i, sqrt(pow((double)galaxy_for_all_pair[i].forceX, 2) + pow((double)galaxy_for_all_pair[i].forceY, 2)));
    return TRUE;
}

int Barnes_Hut(Body* galaxy, int size)
{
    double result[2];
    //printf("The galaxy %d at (%lf, %lf) has a mss of %lf\n", 0, galaxy[0].posX, galaxy[0].posY, galaxy[0].mass);
    //printf("The galaxy %d at (%lf, %lf) has a mss of %lf\n", 1, galaxy[1].posX, galaxy[1].posY, galaxy[1].mass);
    //Body entity, parent;
    //printf("The entity at (%lf, %lf) has a mss of %lf\n", entity.posX, entity.posY, entity.mass);
    //combine_quadtree( galaxy[0], galaxy[1], entity, entity, &parent);
    //printf("The entity at (%lf, %lf) has a mss of %lf\n", parent.posX, parent.posY, parent.mass);
   // if(cal_force(galaxy[0], galaxy[1],  result))
   //     return FALSE;
   // printf("\nThe force on x is %lf, on y is %lf\n", result[0], result[1]);
    return TRUE;
}

void combine_quadtree(Body up_left, Body up_right, 
Body down_left, Body down_right, Body *parent)
{
    // the mass equals to the total mass of its children
    parent->mass = up_left.mass + up_right.mass + down_left.mass + down_right.mass;
    // mass also decide the positions
    parent->posX = (up_left.mass*up_left.posX + up_right.mass*up_right.posX + down_left.mass*down_left.posX + down_right.mass*down_right.posX)/parent->mass;
    
    parent->posY = (up_left.mass*up_left.posY + up_right.mass*up_right.posY + down_left.mass*down_left.posY + down_right.mass*down_right.posY)/parent->mass;
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
		//printf("**********force %d : %f\n", i, sqrt(pow((double)galaxy[i].forceX, 2) + pow((double)galaxy[i].forceY, 2)));
	}
}

