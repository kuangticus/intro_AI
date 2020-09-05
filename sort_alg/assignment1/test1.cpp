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
    temp->name = "keyGen(*temp)";
    
    return temp;

}
struct ComparePath {
    // bool operator<(const struct node& *path2) const{
    //     return this->pathCost < path2->pathCost;
    // }

    bool operator()(const struct node *path1, const struct node *path2){
        return path1->pathCost > path2->pathCost;
    }
};

int main () {
    int arr[2][3] = {{0, 0, 0}, {3, 3, 1}};
    priority_queue <struct node*, vector <struct node*>, ComparePath> vs;
    struct node* test;

    test = makeinitialNode(arr);
   
    vs.push(test);

    test = makeinitialNode(arr);

    test->pathCost = 10; 
    vs.push(test);

    test = makeinitialNode(arr);

    test->pathCost = 5; 

    vs.push(test);

    test = vs.top();
    vs.pop();
    cout << test->pathCost <<endl;

    test = vs.top();
    vs.pop();
    cout << test->pathCost <<endl;

    test = vs.top();
    vs.pop();
    cout << test->pathCost <<endl;


}
