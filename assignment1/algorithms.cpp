#include "assig1.h"

int expandedNodes = 0;

// overload the compare operater that is used to generate the priority queue
struct ComparePath {
    bool operator()(const struct node *path1, const struct node *path2){
        return path1->pathCost > path2->pathCost;
    }
};

// Function: keyGen 
// Description: this function makes the hash key for the hash tables used
// Parameters: struct node goNode
// Return: key (Hash key is returned)
string keyGen (struct node goNode){
    // essentially the hash key will be the state in a string
    string key;         
    stringstream ss;
    // this uses the string stream to make a key string
    ss << goNode.state[0][0] << goNode.state[0][1] << goNode.state[0][2];
    key = ss.str(); // store the generated string in key
    return key;
}

// Function: makeinitialNode
// Description: makes the initialNode for the future reference
// Parameters: int state[][] 2d array for the state
// Return: node pointer temp
struct node* makeinitialNode(int state[2][3]){

    struct node *temp = new struct node;

    temp->parent = NULL; // the initia node has no parent
    temp->action = -1;  // -1 specifies that it deoes no action are required
    temp->pathCost = 0; // since this is root node cost will be zero
    temp->depth = 0;    // since this is root node no depth

    // this for loop copies all of the the state that is passed in into 
    // the nodes state.
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            temp->state[i][j] = state[i][j]; // coping the states
        }
    } 
    temp->name = keyGen(*temp); // name will be the state in a string
    
    return temp;

}

// Function: goalTest
// Description: this function tests to see if the curr node is the goal state
// Parameters: temp node and int state[][] 2d array for the goal state
// Return: node pointer temp
bool goalTest(struct node temp, int goal[2][3]){
    // this nested for loop simply iterates through and compares all elements
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            // is an element is not the same return false immediately
            if(temp.state[i][j] != goal[i][j]){
                return false;    
            }       
        }
    }  
    // otherwise is everything is the same return true
    return true;
}

// Function: actionIsValid
// Description: this function checks to see if the actions generated are going to be valid states and moves
// Parameters: temp node and int action 0-4, 5 possible actions
// Return: bool true or false
bool actionIsValid(struct node temp, int action){

    if(action == 0){ //put one chicken on the boat
        
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                 //checks if removing one chicken on the left bank makes wolves outnumber chickens and checks to see if there is only one chicken
                if( ((temp.state[0][0] - 1 >= temp.state[0][1]) || (temp.state[0][0] - 1 == 0)) && (temp.state[1][0] + 1 >= temp.state[1][1])){
                    
                    return true; // th action is valid return true
                }
            }
        }
        else{ //if boat is on the right bank
            
            if(temp.state[1][0] >= 1){ //checks if there are greater than or equal to 1 chicken on the right bank 
                //checks if removing one chicken on the right bank makes wolves outnumber chicken 
                if( ((temp.state[1][0] - 1 >= temp.state[1][1]) || (temp.state[1][0] - 1 == 0)) && (temp.state[0][0] + 1 >= temp.state[0][1])){ //checks if removing one chicken on the right bank makes wolves outnumber chickens
                    // return true if the action is valid
                    return true;
                }
            }
        }
    }

    else if(action == 1){   //put two chickens on the boat
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the left bank 
                //checks if removing two chicken on the left bank makes wolves outnumber chickens, or if the bank is 0 after removing
                if( ((temp.state[0][0] - 2 >= temp.state[0][1]) || (temp.state[0][0] - 2 == 0))  && (temp.state[1][0]+2 >= temp.state[1][1] ) ){ 
                    return true;    //returns true if the action is valid
                }         
            }
        }
        else{ //if boat is on the right bank
            if(temp.state[1][0] >= 2){ //checks if there are greater than or equal to 2 chickens on the right bank 
                //checks if removing two chicken on the right bank makes wolves outnumber chickens or if the chickend removes will equal zero
                if( ((temp.state[1][0] - 2 >= temp.state[1][1]) || (temp.state[1][0] - 2 == 0)) && (temp.state[0][0] + 2 >= temp.state[0][1] )){ 
                    return true; // returns true if the action is valid
                }                
            }   
        }   
    }

    else if (action == 2){ //put one wolf on the boat
        if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                if( (temp.state[1][0] >= temp.state[1][1]+1) || temp.state[1][0] == 0){ 
                    return true; // if the action is value then return true
                }         
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 wolf on the left bank 
                //checks if adding a wolf to the right bank outnumbers the chickens on the right bank    
                if((temp.state[0][0] >= temp.state[0][1]+1) || temp.state[0][0] == 0){ 
                    return true; // returns true when the state is valid
                }           
           }
        }   
    }

    else if (action == 3){ //put one wolf and one chicken on the boat
        if(temp.state[0][2] == 1){ //check if the boat is on the left side
            if(temp.state[0][0] >= 1 && temp.state[0][1] >= 1){ // check if there are more than one chicken and one wolf on the left side to avoid -1 issue
                //checks to see if the adding one chicken and one wolf will make the game break
                if((temp.state[1][0]+1 >= temp.state[1][1]+1)){ 
                    return true; // if the action is valid then true
                }   
            }
        }
        else{
            if(temp.state[1][0] >= 1 && temp.state[1][1] >= 1){ //checks if there are greater than or equal to 1 chicken on the left bank 
                if((temp.state[0][0]+1 >= temp.state[0][1]+1)) { //checks if removing one chicken on the left bank and adding  makes wolves outnumber chickens
                    return true; // if the action is valid then true
                }    
            }
        }
    }

    else if (action == 4){  // two wolves
         if(temp.state[0][2] == 1){ //check if boat is on left bank
            if(temp.state[0][1] >= 2){ //checks if there are greater than or equal to 2 wolves on the left bank 
                //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                if((temp.state[1][0] >= temp.state[1][1]+2) || (temp.state[1][0] == 0)){ 
                    return true;
                }   
           }
        }
    
        else{ //if boat is on the right bank
           if(temp.state[1][1] >= 2){ //checks if there are greater than or equal to 1 wolf on the left bank 
                //checks if adding a wolf to the right bank outnumbers the chickens on the right bank
                if( (temp.state[0][0] >= temp.state[0][1]+2) || (temp.state[0][0] == 0)){ 
                    return true;
                }     
           }
        }
    }
    return false; // returns false if the potenial action is invalid applies to all of the if statements
}

// Function: result
// Description: this function calcullates the states after the action haves been generated
// Parameters: temp node and int action 0-4, 5 possible actions, and struct *s
// Return: void type
void result(struct node temp, struct node *s, int action){
    // for loop to assign the s pointe the temp contents for mod.
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            s->state[i][j] = temp.state[i][j];
        }   
    }

    if(action == 0){ //move one chicken
   
        if(s->state[0][2] == 1){ //left
            s->state[0][0] = s->state[0][0] - 1; // minus chicken left
            s->state[1][0] = s->state[1][0] + 1; // add chicken right 
            
            // sets the boat logic
            s->state[0][2] = 0;
            s->state[1][2] = 1;      
        }
        else{ // right
            s->state[1][0] = s->state[1][0] - 1; // add chicken right
            s->state[0][0] = s->state[0][0] + 1; // add chicken left
            
            //sets the boat logic
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }

    else if (action == 1){ // move two chickens
 
        if (s->state[0][2] == 1){ //left
            s->state[0][0] = s->state[0][0] - 2; // subtract two chicken from the left bank
            s->state[1][0] = s->state[1][0] + 2; // add two chickens to the right bank
           
            // sets the boat location logic
            s->state[0][2] = 0;
            s->state[1][2] = 1;
        }
        else {
            s->state[1][0] = s->state[1][0] - 2; // sub two from the right bank
            s->state[0][0] = s->state[0][0] + 2; // add two to the left bank
           
           // sets the boat locatin logic
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }
    
    else if (action == 2 ){ //move one wolf
        if(s->state[0][2] == 1){ //left
            s->state[0][1] = s->state[0][1] - 1; // minus left
            s->state[1][1] = s->state[1][1] + 1;  // add right
           
            // sets up boat configurations
            s->state[0][2] = 0;
            s->state[1][2] = 1;       
        }
        else{
            s->state[1][1] = s->state[1][1] - 1; // minus right
            s->state[0][1] = s->state[0][1] + 1; // add right
           
            // sets up boat configurations
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }

    else if ( action == 3 ){ //move one wolf and one chicken
        if(s->state[0][2] == 1){ //left
            //wolf
            s->state[0][1] = s->state[0][1] - 1; // minus left
            s->state[1][1] = s->state[1][1] + 1; // add right
            //chicken
            s->state[0][0] = s->state[0][0] - 1; // minus left
            s->state[1][0] = s->state[1][0] + 1; // add right

            // sets the boat location logic
            s->state[0][2] = 0;
            s->state[1][2] = 1; 
                   
        }
        else{
            //wolf
            s->state[1][1] = s->state[1][1] - 1; // minus right
            s->state[0][1] = s->state[0][1] + 1; // add left
            //chicken
            s->state[1][0] = s->state[1][0] - 1; // minus right
            s->state[0][0] = s->state[0][0] + 1; // add left

            // sets the boat location logic
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }

    else if (action == 4 ){ //move two wolves
         if (s->state[0][2] == 1){ //left

            s->state[0][1] = s->state[0][1] - 2; // subtract two chicken from the left bank
            s->state[1][1] = s->state[1][1] + 2; // add two chickens to the right bank
            
            // sets the boat location logic
            s->state[0][2] = 0;
            s->state[1][2] = 1;
        }
        else {
            s->state[1][1] = s->state[1][1] - 2; // sub two from the right bank
            s->state[0][1] = s->state[0][1] + 2; // add two to the left bank

            // sets the boat location logic
            s->state[0][2] = 1;
            s->state[1][2] = 0; 
        }
    }
}

// Function: solutionPath
// Description: this function prints out the solution path of the the instructions
// Parameters: goal node, ofstream object
// Return: void type
void solutionPath(struct node* goal, ofstream &out1){

    // stack is used to reverse the reversed list
    stack <int> actions;
    struct node* currNode = goal;
    struct node* nextNode = goal->parent;

    // action word bank
    string list [5];
    list[0] = "1) Move 1 chicken across.";
    list[1] = "2) Move 2 chicken across.";
    list[2] = "3) Move 1 wolf across.";
    list[3] = "4) Move 1 chicken and 1 wolf across.";
    list[4] = "5) Move 2 wolves across.";
    
    // generating the solution path
    while(nextNode != NULL){
        // pushing into a stack so that the order is corret
        actions.push(currNode->action);
        currNode = nextNode;
        nextNode = currNode->parent;
    }

    cout << "Path Length: " << actions.size() << endl;

    // this while loop pops the stack to get the instruction printed
    while(!actions.empty()){
        // printing to the cout and the ofstream
        cout << list[actions.top()] << endl;
        out1 << list[actions.top()] << endl;
        actions.pop();
    }
}

// Function: Heuristic 
// Description: this function will get the path cost from the cur node to goal node
// Parameters: s* node, 
// Return: int 
int hueristic(struct node* s, int goalState[2][3]){
    int n;
    if(goalState[0][2] == 1){ // if the boat is left side
        n = s->state[1][0] + s->state[1][1]; // add the wolves and chicken
    }
    else{ // if the boat is right side
        n = s->state[0][0] + s->state[0][1]; // add the wovles and chicken
    }
    
    if(n == 1){
        return 1; // if there is only one chicken on the bank
    }
    else if(goalState[0][2] != s->state[0][2] || goalState[1][2] != s->state[1][2]){
        return (n-2)*2+1; // this will be the cost of the curr node to the goal stata
    }
    else{
        return (n+1-2)*2+1+1; // if the goal state is the opposite side then +1 accouts for the extra move
    }


}

// Function: bfs
// Description: this function will finds the goal node of situation 
// Parameters: ofstream out1, goalstate, initstate
// Return: node *
struct node* bfs(int initState[2][3], int goalState[2][3], ofstream & out1){

    unordered_map <string, struct node*> closed;
    queue <struct node*> fringe;
    struct node* currNode;
    struct node* s;
    vector <string> vs;
    struct node* temp;
    
    // starts the queue off with the initial state
    fringe.push(makeinitialNode(initState)); 

    while(true){
        // if the fring is empty
        if(fringe.empty()){
            // iterate throught the vs of nodes
            // and free everything associated with the vs
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free memory
                    closed.erase(vs[i]); // erasing element from the closed list
                }
            }
            // puting output to terminal and text file
            cout << "fail" <<endl;
            out1 << "fail" <<endl;
            return NULL;
        }
        // move the the node forward
        currNode = fringe.front();
        fringe.pop(); // dequeues the node
        vs.push_back(currNode->name); //pushing the name key into vs

        // we run goal test here
        if(goalTest(*currNode, goalState)){
            // if goal then output to the terminal and the output file
            
            cout << "Goal Name: " << currNode->name <<endl;
            out1 << "Goal Name: " << currNode->name <<endl;

            cout << "Goal Pathcost: " << currNode->pathCost <<endl;
            out1 << "Goal Pathcost: " << currNode->pathCost <<endl;
            
            cout << "Nodes Expanded: " << expandedNodes <<endl; 
            out1 << "Nodes Expanded: " << expandedNodes <<endl;
            
            solutionPath(currNode, out1); // this will print out the solution path
            // instruction to solve the problem will be here as well
            // here we are clearing things from the hash table by uisng a hash table for comparison
            for(int i = 0; i < fringe.size(); i++){
                // this following lines of code will store all the names on the fringe and 
                // into a hash map
                temp = fringe.front();
                fringe.pop();
                if(closed.find(temp->name) == closed.end()){
                    closed[temp->name] = temp; 
                }
            }
            // this loop used the hash map function to free the memory that is left over from before
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free the mem
                    closed.erase(vs[i]); // dele from the hash map
                }
            }
            // printing to know that everything works
            cout << "success" << endl;
            out1 << "success" << endl;
            return currNode;
        }

        // this is an action generation function
        if(closed.find(currNode->name) == closed.end()){
            closed[currNode->name] = currNode;
            expandedNodes++;
            // this will keep track of all the nodes expanded 
            for(int i = 0; i < 5; i++){ // generates action from 0-4
                if(actionIsValid(*currNode, i)){
                    s = new struct node;
                    result(*currNode, s, i); // this will edit the state of node
                    s->parent = currNode; // this will get the currNode pointed to by the 
                    s->name = keyGen(*s); // this will generate name of key for hash 
                    s->action = i; // action is given is the action is given to the 
                    s->pathCost = currNode->pathCost + 1; // path cost is incrmented
                    s->depth = currNode->depth + 1; // depth of the node is incremented
                    fringe.push(s); // then the expandeed nodes are pushed into the fringe.
                }
            }
        }
        else{
            delete currNode; // dele the curr node to rid mem leaks
        }      
    }
}
// Function: dfs
// Description: this function will finds the goal node of situation 
// Parameters: ofstream out1, goalstate, initstate
// Return: node *
struct node* dfs(int initState[2][3], int goalState[2][3], ofstream & out1){

    unordered_map <string, struct node*> closed;
    stack <struct node*> fringe;
    struct node* currNode;
    struct node* s;
    vector <string> vs;
    struct node* temp;
    
    // starts the queue off with the initial state
    fringe.push(makeinitialNode(initState));

    while(true){
        // if the fring is empty
        if(fringe.empty()){
            // iterate throught the vs of nodes
            // and free everything associated with the vs
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free memory
                    closed.erase(vs[i]);  // erasing element from the closed list
                }
            }
            // puting output to terminal and text file
            cout << "fail" <<endl;
            out1 << "fail" <<endl;
            return NULL;
        }
        // move the the node forward
        currNode = fringe.top();
        fringe.pop(); // dequeues the node
        vs.push_back(currNode->name); //pushing the name key into vs

        // we run goal test here
        if(goalTest(*currNode, goalState)){
            // if goal then output to the terminal and the output file
            
            cout << "Goal Name: " << currNode->name <<endl;
            out1 << "Goal Name: " << currNode->name <<endl;

            cout << "Goal Pathcost: " << currNode->pathCost <<endl;
            out1 << "Goal Pathcost: " << currNode->pathCost <<endl;
            
            cout << "Nodes Expanded: " << expandedNodes <<endl; 
            out1 << "Nodes Expanded: " << expandedNodes <<endl;
            
            solutionPath(currNode, out1);// this will print out the solution path
            // instruction to solve the problem will be here as well
            // here we are clearing things from the hash table by uisng a hash table for comparison
            
            for(int i = 0; i < fringe.size(); i++){
                // this following lines of code will store all the names on the fringe and 
                // into a hash map
                temp = fringe.top();
                fringe.pop();
                if(closed.find(temp->name) == closed.end()){
                    closed[temp->name] = temp;
                }
            }
            // this loop used the hash map function to free the memory that is left over from before
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free the mem
                    closed.erase(vs[i]); // dele from the hash map
                }
            }
            // printing to know that everything works
            cout << "success" <<endl;
            out1 << "success" <<endl;
            return currNode;

        }

        // this is an action generation function
        if(closed.find(currNode->name) == closed.end()){
            closed[currNode->name] = currNode;
            expandedNodes++;
            // this will keep track of all the nodes expanded 
            for(int i = 0; i < 5; i++){ // generates action from 0-4
                if(actionIsValid(*currNode, i)){
                    s = new struct node;
                    result(*currNode, s, i); // this will edit the state of node
                    s->parent = currNode; // this will get the currNode pointed to by the 
                    s->name = keyGen(*s); // this will generate name of key for hash 
                    s->action = i; // action is given is the action is given to the 
                    s->pathCost = currNode->pathCost + 1; // path cost is incrmented
                    s->depth = currNode->depth + 1; // increment the depth
                    fringe.push(s); // push s into the fringe
                }
            }
        }
        else{
            delete currNode; // this will free the memory 
        }      
    }
}
// Function: iddfs
// Description: this function will finds the goal node of situation 
// Parameters: ofstream out1, goalstate, initstate
// Return: node *
struct node* iddfs(int initState[2][3], int goalState[2][3], ofstream & out1){

    unordered_map <string, struct node*> closed;
    stack <struct node*> fringe;
    struct node* currNode;
    struct node* s;
    vector <string> vs;
    struct node* temp;
    int limit = 0; // this wil be zero when the the function is called
    int maxDepth = MAXDEPTH; // this will be the max limit 
    
    fringe.push(makeinitialNode(initState)); // intial state is passeed in

    while(true){
        // if the limit is less than global max iters
        if(fringe.empty() && limit <= maxDepth){
           limit++; // increment the limit 
           // clear the for list and the hash and do memory frees
           for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]];
                    closed.erase(vs[i]);
                }
            }
            // re push the initial node since a solution was found at depth l
            fringe.push(makeinitialNode(initState));
        }
        // for this else will be basically return that there is no solution 
        else if(fringe.empty() && limit > maxDepth){ // means that no sol
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]];
                    closed.erase(vs[i]);
                }
            }
            // explict check show for fails
            cout << "fail" <<endl;
            out1 << "fail" <<endl;
            return NULL; // will return null for fail
        }
        // move the the node forward
        currNode = fringe.top();
        fringe.pop(); // dequeues the node
        vs.push_back(currNode->name); //pushing the name key into vs

        // we run goal test here
        if(goalTest(*currNode, goalState)){
            // if goal then output to the terminal and the output file
            
            cout << "Goal Name: " << currNode->name <<endl;
            out1 << "Goal Name: " << currNode->name <<endl;

            cout << "Goal Pathcost: " << currNode->pathCost <<endl;
            out1 << "Goal Pathcost: " << currNode->pathCost <<endl;
            
            cout << "Nodes Expanded: " << expandedNodes <<endl; 
            out1 << "Nodes Expanded: " << expandedNodes <<endl;
            
            solutionPath(currNode, out1); // this will print out the solution path
            // instruction to solve the problem will be here as well
            // here we are clearing things from the hash table by uisng a hash table for comparison
            
            for(int i = 0; i < fringe.size(); i++){
                // this following lines of code will store all the names on the fringe and 
                // into a hash map
                temp = fringe.top();
                fringe.pop();
                if(closed.find(temp->name) == closed.end()){
                    closed[temp->name] = temp;
                }
                
            }
            // this loop used the hash map function to free the memory that is left over from before
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free the mem
                    closed.erase(vs[i]); // delete from the hash map
                }
            }
            // printing to know that everything works
            cout << "success" <<endl;
            out1 << "success" <<endl;
            return currNode;
        }
        // this is an action generation function
        if(closed.find(currNode->name) == closed.end()){
            closed[currNode->name] = currNode;
            expandedNodes++;
            // this will keep track of all the nodes expanded
            for(int i = 0; i < 5; i++){ // generates action from 0-4
                if(actionIsValid(*currNode, i) && currNode->depth <= limit){
                    s = new struct node;
                    result(*currNode, s, i); // this will edit the state of node
                    s->parent = currNode; // this will get the currNode pointed to by the 
                    s->name = keyGen(*s); // this will generate name of key for hash 
                    s->action = i;        // action is given is the action is given to the 
                    s->pathCost = currNode->pathCost + 1; // path cost is incrmented
                    s->depth = currNode->depth + 1; // increment the depth
                    fringe.push(s); // push s into the fringe
                }
            }
        }

        // this chunck if statement will check for when the node has been seen so it overwrites the one deeper
        else if(closed.find(currNode->name) != closed.end()){
            temp = closed[currNode->name]; // this is the temp that will store the hash map access
            if(temp->depth > currNode->depth){
                delete temp; // deletes temp is the there is shallower same node
                closed[currNode->name] = currNode; 
                expandedNodes++;  // expanded the nodes 
                for(int i = 0; i < 5; i++){  // if the nodes are just expand them 
                    if(actionIsValid(*currNode, i) && currNode->depth <= limit){
                        s = new struct node; //this will edit the state of node
                        result(*currNode, s, i); // this will get the currNode pointed to by the 
                        s->parent = currNode; // this will generate name of key for hash 
                        s->name = keyGen(*s); // action is given is the action is given to the 
                        s->action = i; // path cost is incrmented
                        s->pathCost = currNode->pathCost + 1; // increment the depth
                        s->depth = currNode->depth + 1; 
                        fringe.push(s); // push s into the fringe
                    }
                }
            }
            else{
                delete currNode; // this will free the memory 
            }
        }   
    }
}

// Function: astar
// Description: this function will finds the goal node of situation 
// Parameters: ofstream out1, goalstate, initstate
// Return: node *
struct node* astar(int initState[2][3], int goalState[2][3], ofstream & out1){

    unordered_map <string, struct node*> closed; 
    priority_queue <struct node*, vector <struct node*>, ComparePath> fringe; 
    struct node* currNode; 
    struct node* s;        
    vector <string> vs;    
    struct node* temp;
    
    fringe.push(makeinitialNode(initState)); // intial state is passeed in

    while(true){

        if(fringe.empty()){ 
            // explict check show for fails
            cout << "fail" << endl;
            out1 << "fail" << endl;
            return NULL; // will return null for fail
        }

        currNode = fringe.top(); // move the the node forward
        fringe.pop(); // dequeues the node
        vs.push_back(currNode->name); //pushing the name key into vs

        // we run goal test here
        if(goalTest(*currNode, goalState)){
            // if goal then output to the terminal and the output file

            cout << "Goal Name: " << currNode->name <<endl;
            out1 << "Goal Name: " << currNode->name <<endl;

            cout << "Goal Pathcost: " << currNode->pathCost <<endl;
            out1 << "Goal Pathcost: " << currNode->pathCost <<endl;
            
            cout << "Nodes Expanded: " << expandedNodes <<endl; 
            out1 << "Nodes Expanded: " << expandedNodes <<endl;
            
            solutionPath(currNode, out1); // this will print out the solution path
            // instruction to solve the problem will be here as well
            // here we are clearing things from the hash table by uisng a hash table for comparison
        
            for(int i = 0; i < fringe.size(); i++){
                // this following lines of code will store all the names on the fringe and 
                // into a hash map
                temp = fringe.top();
                fringe.pop();
                if(closed.find(temp->name) == closed.end()){
                    closed[temp->name] = temp;
                }
                
            }
            // this loop used the hash map function to free the memory that is left over from before
            for(int i = 0; i < vs.size(); i++){
                if(closed.find(vs[i]) != closed.end()){
                    delete closed[vs[i]]; // free the mem
                    closed.erase(vs[i]); // delete from the hash map
                }
            }
            
            // printing to know that everything works
            cout << "success" <<endl;
            out1 << "success" <<endl;
            return currNode;

        }
        // this is an action generation function
        if(closed.find(currNode->name) == closed.end()){
            closed[currNode->name] = currNode;
            expandedNodes++;
            // this will keep track of all the nodes expanded 
            for(int i = 0; i < 5; i++){ // generates action from 0-4
                if(actionIsValid(*currNode, i)){ 
                    s = new struct node;
                    result(*currNode, s, i); // this will edit the state of node
                    s->parent = currNode; // this will get the currNode pointed to by the
                    s->name = keyGen(*s);  // this will generate name of key for hash
                    s->action = i; // action is given is the action is given to the
                    s->pathCost = currNode->pathCost + hueristic(s, goalState);  // path cost is incrmented by the hueristic function
                    s->depth = currNode->depth + 1; // increment the depth
                    fringe.push(s); // push s into the fringe
                }
            }
        }
        else{
            delete currNode;
        }      
    }
}