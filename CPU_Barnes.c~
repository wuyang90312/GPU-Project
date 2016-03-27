#include "CPU_Barnes.h"
#include "utils.h"

#define     num     10


int main()
{
    // Assume the number of planets are 1000
    Body* galaxy;
    galaxy = (Body*)malloc(sizeof(Body)*num);

   
    read_csv(galaxy);
    printf("The size of galaxy is %p <= %lf\n", (void*)&galaxy[0], galaxy[5].posX);
    return TRUE;
}


