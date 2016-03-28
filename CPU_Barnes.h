#ifndef _CPU_BARNES_H_
#define _CPU_BARNES_H_
#include "utils.h"
typedef struct{
    Body    current_body;   // current node which can be treated as a body with geo locations and mass
    Body*   ptr_child_ul;   // point to the child node at up-left
    Body*   ptr_child_ur;   // point to the child node at up-right
    Body*   ptr_child_dl;   // point to the child node at down-left
    Body*   ptr_child_dr;   // point to the child node at down-right
}quadtree;

int Barnes_Hut(Body* map, int size);
void combine_quadtree(Body up_left, Body up_right, Body down_left, Body down_right, Body* parent);
#endif
