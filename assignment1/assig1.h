#ifndef assig1
#define assig1

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

bool compareStates();
vector <struct node*> expand();
bool actionIsValid();
void result();
bool goalTest();
void solutionPath(struct node, ofstream&, char**);
void heur();
struct node *bfs (struct node, struct node, struct node*, char**, ofstream &);
void dfs ();
void iddfs ();
void astar ();
void print();
void writeFile();
string keyGen(struct node);

struct node{
    int state[2][3];
    struct node* parent;
    string name;
    int action;
    int pathCost;
    int depth;
};
#endif