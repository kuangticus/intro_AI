#include "assig1.h"

using namespace std;

struct node {
    int state[2][3];
    struct node* parent;
    int action;
    int pathCost;
    int depth;

};

int main(int argc, char *argv[]){
    int initState[2][3]; //stores initial state for comp later
    int goalState[2][3]; // stores goal states for comp later
    int temp = 0;    
    string line1, line2;
    ifstream in1, in2; // instream
    ofstream out1;     // outstream

    in1.open(argv[1]); // opening intial state file
    in2.open(argv[2]); // opening goal state file
    out1.open(argv[4]); // opening file for writing by user
 
    //init state getline for values used for intial states values
    if(in1.is_open()){
        getline(in1, line1);
        getline(in1, line2);
    }

    // for loop used to get the the str values into ints
    for(int i = 0; i < line1.length(); i++){
        if(i%2 == 0){
            initState[0][temp] = int(line1[i])-48;
            temp++;
        }
    }
    temp = 0;
    
    // for loop used to get the the str values into ints   
    for (int i=0; i<line2.length(); i++){
        if(i%2 == 0){
            initState[1][temp] = int(line2[i])-48;
            temp++;
        }
    }
    
    //goal state
    temp = 0;
    
    if(in2.is_open()){
        getline(in2, line1);
        getline(in2, line2);
    }

    for(int i = 0; i < line1.length(); i++){
        if(i % 2 == 0){
            goalState[0][temp] = int(line1[i])-48;
            temp++;
        }
    }
    temp = 0;
   
    for (int i=0; i<line2.length(); i++){
        if(i % 2 == 0){
            goalState[1][temp] = int(line2[i])-48;
            temp++;
        }
    }

    in1.close(); //closing text1 intial state
    in2.close(); //closing text2 goal state
    
    string modes[4] = {"bfs", "dfs", "iddfs", "astar"}; // creating a array for mode compare
   
    if ( argc != 5 ){  // exit the program is there isnt the correct amount of args
        cout << "Not the correct number of arguments!" << endl; 
        return 0;
    }

    if ( argv[3] == modes[0] )
        bfs();
    else if ( argv[3] == modes[1] )
        dfs();
    else if ( argv[3] == modes[2] )
        iddfs();
    else if ( argv[3] == modes[3] )
        astar();
    else 
        cout << "Mode: " << argv[3] << " does not exist!" << endl;


    // insert code for writing to file here
    
    return 0;
}

void bfs () {
    cout << "bfs" << endl;
}
void dfs() {
    cout << "dfs" << endl;
}
void iddfs(){
    cout << "iddfs" << endl;
}
void astar(){
    cout << "astar" << endl;
}