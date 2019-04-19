#include "assig1.h"

int main(int argc, char *argv[]){
    int initState[2][3]; //stores initial state for comp later
    int goalState[2][3]; // stores goal states for comp later
    int temp = 0;    
    string line1, line2;
    ifstream in1, in2; // instream
    ofstream out1;     // outstream
    struct node* r1;

    in1.open(argv[1]); // opening intial state file
    in2.open(argv[2]); // opening goal state file
    out1.open(argv[4]); // opening file for writing by user
 
    //init state getline for values used for intial states values
    if(in1.is_open()){ // this will be the if statement that gets the init state
        getline(in1, line1, ',');  // chicken left side
        initState[0][0] = stoi(line1);

        getline(in1, line1, ','); // wolves left side
        initState[0][1] = stoi(line1);

        getline(in1, line1);  // boat left side
        initState[0][2] = stoi(line1);
        
        
        getline(in1, line2, ','); // chicken right side
        initState[1][0] = stoi(line2);

        getline(in1, line2, ','); // wolves right side
        initState[1][1] = stoi(line2);

        getline(in1, line2); // boat left side
        initState[1][2] = stoi(line2);
    }

    if(in2.is_open()){ // goal state of the puzzle
        getline(in2, line1, ','); // left side chicken
        goalState[0][0] = stoi(line1);

        getline(in2, line1, ','); // left side wolves
        goalState[0][1] = stoi(line1);

        getline(in2, line1);  // left side boat pos.
        goalState[0][2] = stoi(line1);
        
        
        getline(in2, line2, ',');  // rigth side chicken
        goalState[1][0] = stoi(line2);

        getline(in2, line2, ','); // left side wolves
        goalState[1][1] = stoi(line2);

        getline(in2, line2); // left side boat pos.
        initState[1][2] = stoi(line2);
    }

    in1.close(); //closing text1 intial state
    in2.close(); //closing text2 goal state
    
    string modes[4] = {"bfs", "dfs", "iddfs", "astar"}; // creating a array for mode compare
   
    if ( argc != 5 ){  // exit the program is there isnt the correct amount of args
        cout << "Not the correct number of arguments!" << endl; 
        return 0;
    }

    if ( argv[3] == modes[0] )                  // is bfs is called
        r1 = bfs(initState, goalState, out1);

    else if ( argv[3] == modes[1] )             // if dfs is called
        r1 = dfs(initState, goalState, out1);

    else if ( argv[3] == modes[2] )             // if iddfs is called
        r1 = iddfs(initState, goalState, out1);

    else if ( argv[3] == modes[3] )             // if astar is called
        r1 = astar(initState, goalState, out1);
    else 
        cout << "Mode: " << argv[3] << " does not exist!" << endl;
    
    out1.close();
    return 0;
}