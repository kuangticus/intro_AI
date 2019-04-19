#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stack>


using namespace std;

int expandedNodes = 0;

struct node{
    int state[2][3];
    struct node* parent;
    string name;
    int action;
    int pathCost;
    int depth;
};

string keyGen (struct node goNode){
    string key;
    stringstream ss;
    ss << goNode.state[0][0] << goNode.state[0][1] << goNode.state[0][2];
    key = ss.str();
    return key;
}

struct node* makeinitialNode(int state[2][3]){

    struct node *temp = new struct node;

    temp->parent = NULL;
    temp->action = -1;
    temp->pathCost = 0;
    temp->depth = 0;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            temp->state[i][j] = state[i][j];
        }
    } 
    temp->name = keyGen(*temp);
    
    return temp;

}
bool goalTest(struct node temp, int goal[2][3]){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            if(temp.state[i][j] != goal[i][j]){
                return false;    
            }       
        }
    }  
    return true;
}


bool actionIsValid(struct node temp, int action){

    if(action == 0){ //put one chicken on the boat
        
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                if( ((temp.state[0][0] - 1 >= temp.state[0][1]) || (temp.state[0][0] - 1 == 0)) && (temp.state[1][0] + 1 >= temp.state[1][1])){ //checks if removing one chicken on the left bank makes wolves outnumber chickens
                    
                    return true;
                }
            }
        }
        else{ //if boat is on the right bank
            
            if(temp.state[1][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the right bank 
                
                if( ((temp.state[1][0] - 1 >= temp.state[1][1]) || (temp.state[1][0] - 1 == 0)) && (temp.state[0][0] + 1 >= temp.state[0][1])){ //checks if removing one chicken on the right bank makes wolves outnumber chickens
                    
                    return true;
                }
            }
        }
    }

    else if(action == 1){   //put two chickens on the boat
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the left bank 
                if( ((temp.state[0][0] - 2 >= temp.state[0][1]) || (temp.state[0][0] - 2 == 0))  && (temp.state[1][0]+2 >= temp.state[1][1] ) ){ //checks if removing two chicken on the left bank makes wolves outnumber chickens
                    return true;
                }         
            }
        }
        else{ //if boat is on the right bank
            if(temp.state[1][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the right bank 
                if( ((temp.state[1][0] - 2 >= temp.state[1][1]) || (temp.state[1][0] - 2 == 0)) && (temp.state[0][0] + 2 >= temp.state[0][1] )){ //checks if removing two chicken on the right bank makes wolves outnumber chickens
                    return true;
                }                
            }   
        }   
    }

    else if (action == 2){ //put one wolf on the boat
        //cout << "action func"<< endl;
        if(temp.state[0][2] == 1){ //check if boat is on left bank
           
            if(temp.state[0][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                if( (temp.state[1][0] >= temp.state[1][1]+1) || temp.state[1][0] == 0){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }         
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                 //cout << "action func 1"<< endl;
                if((temp.state[0][0] >= temp.state[0][1]+1) || temp.state[0][0] == 0){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                   // cout << "action func 22"<< endl;
                    return true;
                }           
           }
        }   
    }

    else if (action == 3){ //put one wolf and one chicken on the boat
        // cout << "seg fault inside action 3?" << endl;
        if(temp.state[0][2] == 1){ //check if the boat is on the left side
            if(temp.state[0][0] >= 1 && temp.state[0][1] >= 1){ // check if there are more than one chicken and one wolf on the left side to avoid -1 issue
                if((temp.state[1][0]+1 >= temp.state[1][1]+1) /*&& ((temp.state[0][0]-1 >= temp.state[0][1]-1) || (temp.state[0][0] - 1 == 0))*/ ){ //checks if removing one chicken on the left bank makes wolves outnumber chickens
                    return true;
                }   
            }
        }
        else{
            if(temp.state[1][0] >= 1 && temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                if((temp.state[0][0]+1 >= temp.state[0][1]+1) /*&& ((temp.state[1][0]-1 >= temp.state[1][1]-1) || (temp.state[0][0] - 1 == 0))*/ ){ //checks if removing one chicken on the left bank and adding  makes wolves outnumber chickens
                    return true;
                }
               
            }
        }
    }

    else if (action == 4){  // two wolves
         if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][1] >= 2){ //checks if there are greater than or equal to 2 wolves on the left bank 
                if((temp.state[1][0] >= temp.state[1][1]+2) || (temp.state[1][0] == 0)){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
               
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 2){ //checks if there are greater than or equal to 1 wolf on the left bank 
                if( (temp.state[0][0] >= temp.state[0][1]+2) || (temp.state[0][0] == 0)){ //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                    return true;
                }
              
           }
        }
    }
    return false;
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
            
            s->state[0][2] = 0;
            s->state[1][2] = 1;      
        }
        else{ // right
            s->state[1][0] = s->state[1][0] - 1;
            s->state[0][0] = s->state[0][0] + 1;
            
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }

    else if (action == 1){ // move two chickens
 
        if (s->state[0][2] == 1){ //left
            s->state[0][0] = s->state[0][0] - 2; // subtract two chicken from the left bank
            s->state[1][0] = s->state[1][0] + 2; // add two chickens to the right bank
           
            s->state[0][2] = 0;
            s->state[1][2] = 1;
        }
        else {
            s->state[1][0] = s->state[1][0] - 2; // sub two from the right bank
            s->state[0][0] = s->state[0][0] + 2; // add two to the left bank
           
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }
    
    else if (action == 2 ){ //move one wolf
        if(s->state[0][2] == 1){ //left
            s->state[0][1] = s->state[0][1] - 1;
            s->state[1][1] = s->state[1][1] + 1; 
           
            s->state[0][2] = 0;
            s->state[1][2] = 1;       
        }
        else{
            s->state[1][1] = s->state[1][1] - 1;
            s->state[0][1] = s->state[0][1] + 1;
           
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
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

            s->state[0][2] = 0;
            s->state[1][2] = 1; 
                   
        }
        else{
            //wolf
            s->state[1][1] = s->state[1][1] - 1;
            s->state[0][1] = s->state[0][1] + 1;
            //chicken
            s->state[1][0] = s->state[1][0] - 1;
            s->state[0][0] = s->state[0][0] + 1;

            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }

    else if (action == 4 ){ //move two wolves
         if (s->state[0][2] == 1){ //left

            s->state[0][1] = s->state[0][1] - 2; // subtract two chicken from the left bank
            s->state[1][1] = s->state[1][1] + 2; // add two chickens to the right bank
            
            s->state[0][2] = 0;
            s->state[1][2] = 1;
        }
        else {
            s->state[1][1] = s->state[1][1] - 2; // sub two from the right bank
            s->state[0][1] = s->state[0][1] + 2; // add two to the left bank

            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }
}

void solutionPath(struct node* goal){

    stack <int> actions;
    struct node* currNode = goal;
    struct node* nextNode = goal->parent;

    string list [5];
    list[0] = "1) Move 1 chicken across.";
    list[1] = "2) Move 2 chicken across.";
    list[2] = "3) Move 1 wolf across.";
    list[3] = "4) Move 1 chicken and 1 wolf across.";
    list[4] = "5) Move 2 wolves across.";
    
    while(nextNode != NULL){
        actions.push(currNode->action);
        currNode = nextNode;
        nextNode = currNode->parent;
    }

    cout << "Size of path" << actions.size() << endl;

    while(!actions.empty()){
        cout << list[actions.top()] << endl;
        actions.pop();
    }
}

struct node* dfs(int initState[2][3], int goalState[2][3]){

    unordered_map <string, struct node*> closed;
    stack <struct node*> fringe;
    struct node* currNode;
    struct node* s;
    vector <string> vs;
    struct node* temp;
    // struct node* testparent = new struct node;
    // testparent->name = "parent";


    
    fringe.push(makeinitialNode(initState));
    // fringe.push(testparent);

    while(true){

        if(fringe.empty()){
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]];
                    closed.erase(vs[i]);
                }
            }
            cout << "fail" <<endl;
            return NULL;
        }


        currNode = fringe.top();
        fringe.pop();
        vs.push_back(currNode->name);

        // cout << currNode->name <<endl;
        //closed[currNode->name] = currNode;

        if(goalTest(*currNode, goalState)){
            
            cout << "Goal Name: " << currNode->name <<endl;
            cout << "Goal Pathcost: " << currNode->pathCost <<endl;
            cout << "Nodes Expanded: " << expandedNodes <<endl; 
            
            solutionPath(currNode);
            
            for(int i = 0; i < fringe.size(); i++){
                temp = fringe.top();
                fringe.pop();
                if(closed.find(temp->name) == closed.end()){
                    closed[temp->name] = temp;
                }
                
            }
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]];
                    closed.erase(vs[i]);
                }
            }
            

            cout << "success" <<endl;
            return currNode;

        }

        if(closed.find(currNode->name) == closed.end()){
            closed[currNode->name] = currNode;
            expandedNodes++;
            for(int i = 0; i < 5; i++){
                if(actionIsValid(*currNode, i)){
                    s = new struct node;
                    result(*currNode, s, i);
                    s->parent = currNode;
                    s->name = keyGen(*s);
                    s->action = i;
                    s->pathCost = currNode->pathCost + 1; 
                    s->depth = currNode->depth + 1;
                    fringe.push(s);
                }
            }
        }
        else{
            delete currNode;
        }      
    }





}

int main(){

    int arr[2][3] = {{0, 0, 0}, {100, 95, 1}};
    int arr2[2][3] = {{100, 95, 1}, {0, 0, 0}};

    struct node* goal;


   goal = dfs(arr, arr2);



    
    return 0;
}
