#include "assig1.h"


struct node* expand(struct node* temp){

    struct node* successors; //needs to be a data structure of some kind not just an array unless we can append to an array. Maybe a vector
    struct node* s;
    

    for(int i = 0; i < 6; i++){

        if(actionIsValid(temp, i)){
            s = new struct node;
            s->parent = temp;
            s->action = i;            
            result(temp, s, i);
            s->pathCost = temp->pathCost + stepCost(temp, i, s); 
            s->depth++;
            successors.append(s);
        }


    }

    
    return successors;
}

struct node bfs(struct node initState, struct node goalState, struct node failNode){

    struct node* temp;
    struct node* expanded; //same data structure as successors
    hashtable closed; //create hashtable for bfs
    queue fringe;   //queue for nodes 
    fringe.push(initState); //pushes initial state on the queue

    while(true){
        if(fringe.isEmpty()){ 
            return failNode;    //returns failure if fringe is empty
        }
        
        temp = &fringe.pop(); //puts the first node to be expanded in a temp variable
        if(goalTest(*temp)){ //checks if the node is a goal state
            return *temp;    // returns the node if it is a goal state
        }


        if(!closed.contains(temp->state)){ //checks if the closed list contains the node to be expanded

            closed.add(temp->state);       //adds the node to the closed list
            expanded = expand(temp);       //expands the node and returns successors
            
            for(int i = 0; i < expanded.length(); i++){
                
                // if(compareState(expanded[i], failNode)){
                //     break;
                // }
                
                fringe.push(expanded[i]); //adds from the expanded list to the fringe list

            }




        }         








    }





}