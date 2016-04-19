#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define     FALSE   -1
#define     TRUE    0

typedef struct{
    double posX, posY;          //position x and y
    double forceX, forceY;      //force acting on object since last frame
    double mass;                //mass of object
}Body;

FILE *fp;

int read_csv(Body* input);
void start_csv(char* filename);
void write_csv(float num1, float num2);
void end_csv();
double cal_force(Body target, Body actor, double result[]);


/*
**  Read data from csv file and store them into the given Body structure
**  param   input: The address where to store the information of geo locations and mass
**  ret     Whether the function is processed successfully
***/
int read_csv(Body* input)
{
    char buffer[1024];  //store the read data from csv file
    char *record,*line;
    int line_idx =0, token_idx;

    FILE *fstream = fopen("./utils/map.csv","r");   // open the csv file
    if(fstream == NULL) // If the file cannot be opened, report error
    {
        printf("\n [ERROR] file opening failed \n");
        return FALSE ;
    }

    // Read the csv file line by line
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
        record = strtok(line,",");  // delimiter token is comma
        token_idx = 0;

        while(record != NULL)
        { 
            double tmp;
            // TODO: increase the precision, c can only reach the millionth decimal place
            tmp = strtod(record, NULL);
            //printf(" %s=>%f ||",record, tmp) ;      //here you can put the record into the array as per your requirement.
            
            // According to token index, assign values to different elements of the Body struct
            if(token_idx == 0)
                input[line_idx].posX = tmp;
            else if (token_idx == 1) 
                input[line_idx].posY = tmp;
            else if (token_idx == 2) 
                input[line_idx].mass = tmp;
            else    // There should not be 4th item in csv file
            {
                printf("\n [ERROR] unkown information appears in file \n");
                return FALSE ;
            }
            record = strtok(NULL,",");  // delimiter token is comma 
            token_idx ++; 
        }
        line_idx++;
    }
    
    fclose(fstream);    //close the csv file
    return TRUE;
}


void start_csv(char* filename)
{
    fp=fopen(filename,"w+");
}

void write_csv(float num1, float num2)
{
    fprintf(fp, "%f,%f\n", num1, num2);
}

void end_csv()
{
    fclose(fp);
}
/*
**  Calculate the force that one entity acts on the other
**  param   target: The body on which force is acting 
            actor:  The body which acts force
            result: 2-d array which store the force on x,y dimension 
**  ret     the distance b/t 2 points
***/
// Here, the universal gravitational constant is omitted to simplify the compuation
double cal_force(Body target, Body actor, double result[])
{
    double dist_x, dist_y, dist_sqr, dist, force;
    dist_x = actor.posX - target.posX;  // distance in x-coordinate, point to the actor
    dist_y = actor.posY - target.posY;  // distance in y-coordinate, point to the actor
    dist_sqr = pow(dist_x, 2) + pow(dist_y, 2);  // squared value of distance b/t actor and target

    if(dist_sqr == 0) // in case of 2 bodies are in exactly the same positions
    {
        printf("\n [ERROR] Bodies are overlapped \n");
        return FALSE;
    }
    dist = sqrt(dist_sqr);
    force = actor.mass*target.mass/dist_sqr;    // calculate the force and omit the unviersal gravitational constant
    result[0] = force*dist_x/dist;  // force on x-coord toward actor
    result[1] = force*dist_y/dist;  // force on y-coord toward actor
    
    return dist;
}

#endif
