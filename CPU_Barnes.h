#ifndef _CPU_BARNES_H_
#define _CPU_BARNES_H_
#include "utils.h"
typedef struct tree{
    int     state;
    Body*    current_body;   // current node which can be treated as a body with geo locations and mass
    struct tree*   ptr_child[4];   // point to the child node at up-left
    //struct tree*   ptr_child_ur;   // point to the child node at up-right
    //struct tree*   ptr_child_dl;   // point to the child node at down-left
    //struct tree*   ptr_child_dr;   // point to the child node at down-right
}quadtree_node;

int Barnes_Hut(Body* map, int size);
//void copy_node(quadtree_node* node, Body planet);
int cal_force_tree(quadtree_node* node, Body* target, double edge);
void combine_quadtree(Body* newComer1, Body* newComer2, Body *parent);
int insert_node(quadtree_node* node, Body* planet,double center[], double edge);
int select_section(quadtree_node* parent, Body* entity, double center[], double new_center[], double edge);
#endif
