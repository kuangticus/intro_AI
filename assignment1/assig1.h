#ifndef assig1
#define assig1

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

bool compareStates();
struct node* expand();
bool actionIsValid();
void result();
bool goalTest();
void solutionPath();
//void graphSearch();
void heur();
void bfs ();
void dfs ();
void iddfs ();
void astar ();
void print();
void writeFile();


struct node{
    int state[2][3];
    struct node* parent;
    int action;
    int pathCost;
    int depth;

};





#endif