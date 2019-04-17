#include "assig1.h"

bool actionIsValid(struct node temp, int action){

    if(action == 0){ //put one chicken on the boat
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                if(temp.state[0][0] - 1 > temp.state[0][1]){ //checks if removing one chicken on the left bank makes wolves outnumber chickens
                    return true;
                }
                return false;
            }
        }
        else{ //if boat is on the right bank
            if(temp.state[1][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the right bank 
                if(temp.state[1][0] - 1 >= temp.state[1][1]){ //checks if removing one chicken on the right bank makes wolves outnumber chickens
                    return true;
                }
                return false;
            }
        }
    }

    else if(action == 1){   //put two chickens on the boat
            if(temp.state[0][2] == 1){ //check if boat is on left bank
                if(temp.state[0][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the left bank 
                    if(temp.state[0][0] - 2 >= temp.state[0][1]){ //checks if removing two chicken on the left bank makes wolves outnumber chickens
                        return true;
                    }
                    return false;
                }
            }
           else{ //if boat is on the right bank
                if(temp.state[1][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the right bank 
                    if(temp.state[1][0] - 2 >= temp.state[1][1]){ //checks if removing two chicken on the right bank makes wolves outnumber chickens
                        return true;
                    }
                    return false;
                }   
            }   
    }

    else if (action == 2){ //put one wolf on the boat
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                if(temp.state[1][0] >= temp.state[1][1]+1){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
               return false;
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                if(temp.state[0][0] >= temp.state[0][1]+1){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
               return false;
           }
        }
    }

    else if (action == 3){ //put one wolf and one chicken on the boat
        if(temp.state[0][2] == 1){ //check if the boat is on the left side
            if(temp.state[0][0] >= 1 && temp.state[0][1] >= 1){ // check if there are more than one chicken and one wolf on the left side to avoid -1 issue
                if((temp.state[0][0] - 1 > temp.state[0][1]) && (temp.state[1][0] >= temp.state[1][1]+1)){ //checks if removing one chicken on the left bank makes wolves outnumber chickens
                    return true;
                }
                return false;
            }
        }
        else{
            if(temp.state[1][0] >= 1 && temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                if((temp.state[1][0] - 1 > temp.state[1][1]) && (temp.state[0][0] >= temp.state[0][1]+1)){ //checks if removing one chicken on the left bank and adding  makes wolves outnumber chickens
                    return true;
                }
                return false;
            }
        }
    }

    else if (action == 4){  // two wolves
         if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][1] >= 2){ //checks if there are greater than or equal to 2 wolves on the left bank 
                if(temp.state[1][0] >= temp.state[1][1]+2){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
               return false;
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 2){ //checks if there are greater than or equal to 1 wolf on the left bank 
                if(temp.state[0][0] >= temp.state[0][1]+2){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
               return false;
           }
        }
    }
}

void result(struct node temp, struct node *s, int action){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            s->state[i][j] = temp.state[i][j];
        }   
    }

    if(action == 0){ //move one chicken
        if(s->state[0][2] == 1){ //left
            s->state[0][0] = s->state[0][0] - 1;
            s->state[1][0] = s->state[1][0] + 1;       
        }
        else{
            s->state[1][0] = s->state[1][0] - 1;
            s->state[0][0] = s->state[0][0] + 1;
        }
    }

    else if (action == 1){ // move two chickens
        if (s->state[0][2] == 1){ //left
            s->state[0][0] = s->state[0][0] - 2; // subtract two chicken from the left bank
            s->state[1][0] = s->state[1][0] + 2; // add two chickens to the right bank
        }
        else {
            s->state[1][0] = s->state[1][0] - 2; // sub two from the right bank
            s->state[0][0] = s->state[0][0] + 2; // add two to the left bank
        }
    }
    
    else if (action == 2 ){ //move one wolf
        if(s->state[0][2] == 1){ //left
            s->state[0][1] = s->state[0][1] - 1;
            s->state[1][1] = s->state[1][1] + 1;       
        }
        else{
            s->state[1][1] = s->state[1][1] - 1;
            s->state[0][1] = s->state[0][1] + 1;
        }

    }

    else if ( action == 3 ){ //move one wolf and one chicken
        if(s->state[0][2] == 1){ //left
            //wolf
            s->state[0][1] = s->state[0][1] - 1;
            s->state[1][1] = s->state[1][1] + 1;
            //chicken
            s->state[0][0] = s->state[0][0] - 1;
            s->state[1][0] = s->state[1][0] + 1;       
        }
        else{
            //wolf
            s->state[1][1] = s->state[1][1] - 1;
            s->state[0][1] = s->state[0][1] + 1;
            //chicken
            s->state[1][0] = s->state[1][0] - 1;
            s->state[0][0] = s->state[0][0] + 1;
        }
    }

    else if (action == 4 ){ //move two wolves
         if (s->state[0][2] == 1){ //left
            s->state[0][1] = s->state[0][1] - 2; // subtract two chicken from the left bank
            s->state[1][1] = s->state[1][1] + 2; // add two chickens to the right bank
        }
        else {
            s->state[1][1] = s->state[1][1] - 2; // sub two from the right bank
            s->state[0][1] = s->state[0][1] + 2; // add two to the left bank
        }
    }
}

string keyGen (struct node goNode){
    string key;
    key = to_string(goNode->state[0][0]) + to_string(goNode->state[0][1]) + to_string(goNode->state[0][2]) 
        + to_string(goNode->action);  // changes the ints to string for key generation for the hash table
    return key;
}

vector <struct node*> expand(struct node* temp){

    vector <struct node*> successors; // vector //needs to be a data structure of some kind not just an array unless we can append to an array. Maybe a vector
    struct node* s;
    
    for(int i = 0; i < 5; i++){

        if(actionIsValid(*temp, i)){  // this function checks see if the
            s = new struct node;
            s->parent = temp;
            s->action = i;            
            result(*temp, s, i);
            s->pathCost = temp->pathCost + 1;//stepCost(temp, s, i); 
            s->depth++;
            s->name = keyGen(*s);
            successors.append(s);
        }
    }
    return successors;
}

struct node bfs(struct node initState, struct node goalState, struct node failNode){

    struct node* temp;  // going to expand node?
    vector <struct node*> expanded; //same data structure as successors
    unordered_map <string, struct node*> closed; //create hashtable for bfs
    queue <struct node> fringe;   //queue for nodes 
    fringe.push(initState); //pushes initial state on the queue

    while(true){
        if(fringe.isEmpty()){ 
            return failNode;    //returns failure if fringe is empty
        }
        
        temp = &fringe.pop(); //puts the first node to be expanded in a temp variable
        if(goalTest(*temp)){ //checks if the node is a goal state
            return *temp;    // returns the node if it is a goal state
        }
        
        if(closed.find(temp->name) == closed.end()){ //checks if the closed list contains the node to be expanded

            closed[temp->name] = temp;    //adds the node to the closed list
            expanded = expand(temp);       //expands the node and returns successors
            
            for(int i = 0; i < expanded.length(); i++){
                
                fringe.push(expanded[i]); //adds from the expanded list to the fringe list

            }
        }         
    }
}