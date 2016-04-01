#include "CPU_Barnes.h"

// Assume the number of planets are 10
#define     NUM     10

#define     EDGE     400
// Actual theta is 0.5, but since our edge is halved, so the theta should be halved
#define     THETA   0.25 
int main()
{
    // Declare the pointer and allocate the memory
    Body* galaxy;
    galaxy = (Body*)calloc(NUM, sizeof(Body));

    // read data from csv file
    if(read_csv(galaxy))
        return FALSE;   // if the function fail, return false
    
    if(galaxy == NULL)
    {
        printf("\n [ERROR] Empty Space \n");
        return FALSE;
    }
    Barnes_Hut(galaxy, NUM);

    return TRUE;
}

int Barnes_Hut(Body* galaxy, int size)
{
    //double result[2];
    double center[2] = {0,0};
    //printf("The galaxy %d at (%lf, %lf) has a mss of %lf\n", 0, galaxy[0].posX, galaxy[0].posY, galaxy[0].mass);
    //printf("The galaxy %d at (%lf, %lf) has a mss of %lf\n", 1, galaxy[1].posX, galaxy[1].posY, galaxy[1].mass);
    //Body entity, parent;
    //printf("The entity at (%lf, %lf) has a mss of %lf\n", entity.posX, entity.posY, entity.mass);
    //combine_quadtree( galaxy[0], galaxy[1], entity, entity, &parent);
    //printf("The entity at (%lf, %lf) has a mss of %lf\n", parent.posX, parent.posY, parent.mass);
   // if(cal_force(galaxy[0], galaxy[1],  result))
   //     return FALSE;
   // printf("\nThe force on x is %lf, on y is %lf\n", result[0], result[1]);
   
    quadtree_node* root;
    root = (quadtree_node*) calloc(1, sizeof(quadtree_node));
    
   /* printf("The node state: %d\n", root->state);
    printf("ul location : %p, ur location : %p, dl location : %p, dr location : %p\n", &root->ptr_child[0], &root->ptr_child[1], &root->ptr_child[2], &root->ptr_child[3]);
    insert_node(root, &galaxy[0], center, EDGE);
    printf("The entity of state %d at (%lf, %lf) has a mass of %lf\n", root->state, root->current_body->posX, root->current_body->posY, root->current_body->mass);
    insert_node(root, &galaxy[1], center, EDGE);
    printf("The node state: %d\n", root[0].state);
    
    printf("root: %f, child1: %f, child21: %f, child22: %d\n", root->current_body->posX, root->ptr_child[3]->current_body->posX, root->ptr_child[3]->ptr_child[0]->current_body->posX,root->ptr_child[2]==NULL);*/
    
    // construct the Quad-tree
    for(int i=0; i < 3; i++)
    {
        //printf("\n>>>>>>>>>The galaxy %d at (%lf, %lf) has a mss of %lf\n", i, galaxy[i].posX, galaxy[i].posY, galaxy[i].mass);
        if(insert_node(root, &galaxy[i], center, EDGE)==FALSE)
        {
            return FALSE;
        }
    }
    //printf("root: %f, child1: %f, child21: %f, child22: %d\n", root->current_body->posX, root->ptr_child[3]->current_body->posX, root->ptr_child[3]->ptr_child[0]->current_body->posX,root->ptr_child[3]->ptr_child[0]->current_body==&galaxy[0]);
    // Calculate the force on each node
    for(int i=0; i < size; i++)
    {
        //printf("\n>>>>>>>>>The galaxy %d has force (%lf, %lf)\n", i, galaxy[i].forceX, galaxy[i].forceY);
        cal_force_tree(root, &galaxy[i],  EDGE);
        printf("\n>>>>>>>>>The galaxy %d has force (%lf, %lf)\n", i, galaxy[i].forceX, galaxy[i].forceY);
    }
    //printf("Theta: %f\n", THETA);
    return TRUE;
}
/*
void copy_node(quadtree_node* node, Body planet)
{
    node->state = 1;
    node->current_body.posX = planet.posX;
    node->current_body.posY = planet.posY;
    node->current_body.mass = planet.mass;
}
*/
int insert_node(quadtree_node* node, Body* planet, double center[], double edge)
{
    double new_edge = edge /2;  // halve the original edge
    //printf("centers at %lf, %lf      with edge of %lf  at state %d\n", center[0], center[1], edge, node->state);
    if(node->state == 0) // If the node of tree is empty, insert this node with current body
    {
       // printf("option 1\n");
        node->state = 1; // state 1 means that the node is an external node
        node->current_body = planet; // the node points to a body representing a planet
    }
    else if(node->state == 1) // If the node is already an external node, make it internal node and shift the original body to the child of the node
    {
       // printf("option 2\n");
        node->state = 2; // state 2 means that the node is an internal node
        
        double center1[2];
        double center2[2];
        int section1 = select_section(node, node->current_body, center, center1, new_edge); // calculate the new center of original body in node
        int section2 = select_section(node, planet, center, center2, new_edge); // calculate the center for new added body
        
        quadtree_node* child_node;
        child_node = (quadtree_node*) calloc(2, sizeof(quadtree_node)); // allocate memory at heap for current node and new node
        
        Body* parent;
        parent = (Body*) calloc(1, sizeof(Body));
        combine_quadtree(node->current_body, planet, parent); // calculate the combination b/t current body and new body
        
        node->ptr_child[section1] = &child_node[0];
        node->ptr_child[section2] = &child_node[1];
       // printf("state: %d   %d; x:%f  y:%f  mss: %f\n", child_node[0].state, child_node[1].state, parent->posX, parent->posY, parent->mass);
        insert_node(node->ptr_child[section1], node->current_body, center1, new_edge); // shift the body from parent node to its child node
        insert_node(node->ptr_child[section2], planet, center2, new_edge); // move the new body to one of child node
        
        node->current_body = parent; // assign the combined result to new node
        
    }else if(node->state == 2)
    {
       // printf("option 3\n");
        double center1[2];
        int section = select_section(node, planet, center, center1, new_edge); // calculate the center for new added body
        
        quadtree_node* child_node;
        child_node = (quadtree_node*) calloc(1, sizeof(quadtree_node)); // allocate the memory at heap for the new node
        
        Body* parent;
        parent = (Body*) calloc(1, sizeof(Body));
        combine_quadtree(node->current_body, planet, parent); // calculate the combination b/t current body and new body
        
        if(node->ptr_child[section] == NULL)
            node->ptr_child[section] = &child_node[0];
        insert_node(node->ptr_child[section], planet, center1, new_edge); // shift the body from parent node to its child node
        
        node->current_body = parent; // assign the combined result to new node
       // printf("state is : %d\n", node->ptr_child[section]);
    }else
    {
        printf("\n [ERROR] Invalid State \n");
        return FALSE;
    }
    
    return TRUE;
}

int cal_force_tree(quadtree_node* node, Body* target, double edge)
{
    if(node==NULL)
    {
        printf("Nil node\n");
    }else
    { 
         printf("node at %lf, %lf      with edge of %lf  at state %d\n", node->current_body->posX, node->current_body->posY, edge, node->state);
        if(node->current_body == target)
        {
            printf("The node is the target\n");
        }else if(node->state == 1) // The node is an external node -> a planet
        {
            printf("         Single Point\n");
            double result[2];
            cal_force(*target, *node->current_body, result);
            target->forceX += result[0];
            target->forceY += result[1];
        }else if(node->state == 2) // The node is an internal node -> mass combination of multiple planets
        {
            
            double crit;
            double result[2];
            double dist = cal_force(*target, *node->current_body, result);
            crit = edge/dist;
            printf("         Center of Mass %lf/%f=%lf\n", edge, dist, crit);
            if(crit < THETA) // If criteria < theta, treat the center of mass as a single planet and return
            {
                target->forceX += result[0];
                target->forceY += result[1];
                return TRUE;
            }else // otherwise, go to all of the children
            {
                double new_edge = edge /2;  // halve the original edge
                cal_force_tree(node->ptr_child[0], target,  new_edge); 
                cal_force_tree(node->ptr_child[1], target,  new_edge);
                cal_force_tree(node->ptr_child[2], target,  new_edge);
                cal_force_tree(node->ptr_child[3], target,  new_edge);
            }
        }else
        {
            printf("\n [ERROR] Force Calculation at Tree structure \n");
            return FALSE;
        }
    }
    return TRUE;
}

int select_section(quadtree_node* parent, Body* entity, double center[], double new_center[], double edge)
{
    int section = -1;
    if( entity->posY >= center[1]) // upper
    {
        new_center[1] = center[1] + edge;
        if(entity->posX <= center[0]) // left
        {
            new_center[0] = center[0] - edge;
            section = 0;
        }
        else //right
        {
            new_center[0] = center[0] + edge;
            section = 1;
        }
    }
    else // bottom
    {
        new_center[1] = center[1] - edge;
        if(entity->posX <= center[0])
        {
            new_center[0] = center[0] - edge;
            section = 2;
        }
        else
        {
            new_center[0] = center[0] + edge;
            section = 3;
        }
    }
    //printf("The section number is %d \n", section);
    return section;
}

void combine_quadtree(Body* newComer1, Body* newComer2, Body *parent)
{
    // the mass equals to the total mass of its children
    parent->mass = newComer2->mass + newComer1->mass;
    // mass also decide the positions
    parent->posX = (newComer1->mass*newComer1->posX + newComer2->mass*newComer2->posX)/parent->mass;
    
    parent->posY = (newComer1->mass*newComer1->posY + newComer2->mass*newComer2->posY)/parent->mass;
}


