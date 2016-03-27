#include "CPU_Barnes.h"

#define     num     10


int main()
{
    // Assume the number of planets are 1000
    Body* galaxy;
    galaxy = (Body*)malloc(sizeof(Body)*num);

   
    read_csv(galaxy);
    //printf("The size of galaxy is %p <= %lf\n", (void*)&galaxy[0], galaxy[9].mass);
    return TRUE;
}

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
    printf("The size of galaxy is %p <= %lf\n", (void*)&input[0], input[0].posX);
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
        //printf("record :");  
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
        //printf("\n") ;
    }
    
    fclose(fstream);    //close the csv file
    return TRUE;
}
