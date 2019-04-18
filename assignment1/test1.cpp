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

struct ComparePath {
    bool operator<(const struct node *& path2){
        return this->pathCost < path2->pathCost;
    }
};

int main () {
    priority_queue <struct node*> vs;
}
