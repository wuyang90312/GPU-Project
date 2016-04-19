#include "utils.h"

int main()
{
    start_csv("trail.csv");
    
    for(int i =0; i< 100; i++)
    {
        write_csv(i, i+100);
    }
    end_csv();
    return TRUE;
}
