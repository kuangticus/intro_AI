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

struct node{
    int state[2][3];
    struct node* parent;
    string name;
    int action;
    int pathCost;
    int depth;
};

int main () {
    unordered_map <string, struct node*> closed;

    struct node *t1, *t2;


    t1= new struct node;

    t1->name = "Bill Cosby";

    string random = "type this";

    closed["sdfsf"] = t1;

    t2 = closed[random];

    cout << t2->name << endl;
    
}
