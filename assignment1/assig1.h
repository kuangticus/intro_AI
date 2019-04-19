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


#define MAXDEPTH 1000

using namespace std;

bool actionIsValid(struct node, int);
void result(struct node, struct node*, int);
bool goalTest(struct node, int [][3]);
void solutionPath(struct node*, ofstream &);
string keyGen(struct node);
struct node *makeinitialNode(int [][3]);
struct node *bfs (int [][3], int [][3], ofstream &);
struct node *dfs (int [][3], int [][3], ofstream &);
struct node *iddfs (int [][3], int [][3], ofstream &);
struct node *astar (int [][3], int [][3], ofstream &);
int hueristic(struct node*, int [][3]);

struct node{
    int state[2][3];
    struct node* parent;
    string name;
    int action;
    int pathCost;
    int depth;
};
#endif