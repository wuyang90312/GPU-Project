#ifndef _CPU_BARNES_H_
#define _CPU_BARNES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define     FALSE   -1
#define     TRUE    0

typedef struct{
    double posX, posY;          //position x and y
    double velX, velY;          //velocity x and y
    double forceX, forceY;      //force acting on object since last frame
    double mass;                //mass of object
}Body;

int read_csv(Body* input);

#endif
