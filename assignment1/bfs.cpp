#include "assig1.h"


struct node* expand(struct node* temp){

    struct node* sucessors;
    struct node* s;

    for(int i = 0; i < 7; i++){

        s = new struct node;
        s->parent = temp;
        action(temp, i);

    }


}

struct node bfs(struct node initState, struct node goalState, struct node failNode){

    struct node* temp;
    struct node* expanded;
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
            
            for(int i = 0; i < 6; i++){
                
                if(compareState(expanded[i], failNode)){
                    break;
                }
                
                fringe.push(expanded[i]);

            }




        }         








    }





}