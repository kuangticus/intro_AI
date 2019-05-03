/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include <climits>
#include "MinimaxPlayer.h"

using std::vector;
using namespace std;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {
}

MinimaxPlayer::~MinimaxPlayer() {

}

// Function: utility function that will get the utility of the term states
// Para: OthelloBoard
// Description: gets the terminal of the terminal state by subtracting the p1 from the p2
int MinimaxPlayer::utFunc(OthelloBoard *b)
{
	// returns the utility state of the terminal state
	return  b->count_score(b->get_p1_symbol() ) - b->count_score(b->get_p2_symbol() );
}

// Function: getSuccessors 
// Para: creates the successors of the of the player 
vector<OthelloBoard*> MinimaxPlayer::getSuccessors (OthelloBoard *b, char symbol) {
	vector<OthelloBoard*> listOfSuccessors;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ( b->is_legal_move(i, j, symbol)){
				OthelloBoard *temp = new OthelloBoard(*b);
				temp->mutateThisCol(i);				
				temp->mutateThisRow(j);
				temp->play_move(i,j, symbol);
				listOfSuccessors.push_back(temp);
			}
		}
	}
	return listOfSuccessors;
}

int MinimaxPlayer::maxValue (OthelloBoard *b, int &col, int &row)
{
	int maxU = INT_MIN;
	int compareMin=0;
	int bestSol[2];
	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p1_symbol());

	if ( listOfSuccessors.size() == 0 ){
		return utFunc(b);
	}

	for( int i = 0; i < listOfSuccessors.size(); i++ ){
		compareMin = max(maxU, minValue(listOfSuccessors[i], col, row));
		if ( compareMin > maxU )
		{
			maxU = compareMin;
			bestSol[0] = listOfSuccessors[i]->getThisCol();
			bestSol[1] = listOfSuccessors[i]->getThisRow();
		}
	}
	col = bestSol[0];
	row = bestSol[1];

	for (int i = 0; i < listOfSuccessors.size(); i++ )
	{
		delete listOfSuccessors[i];
	}
	return maxU;
}

int MinimaxPlayer::minValue (OthelloBoard *b, int &col, int &row)
{
	int minU = INT_MAX;
	int compareMax=0;
	int bestSol[2];
	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p2_symbol());

	if ( listOfSuccessors.size() == 0 ){
		return utFunc(b);
	}
	
	for (int i = 0; i < listOfSuccessors.size(); i++){
		compareMax = min(minU, maxValue(listOfSuccessors[i], col, row));
		if ( compareMax < minU )
		{
			minU = compareMax;
			bestSol[0] = listOfSuccessors[i]->getThisCol();
			bestSol[1] = listOfSuccessors[i]->getThisRow();
		}
	}
	col = bestSol[0];
	row = bestSol[1];

	for (int i = 0; i < listOfSuccessors.size(); i++ )
	{
		delete listOfSuccessors[i];
	}
	return minU;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row)
{
		int bestMove = minValue(b, col, row);
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
