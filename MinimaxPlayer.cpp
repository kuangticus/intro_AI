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

int MinimaxPlayer::utFunc(OthelloBoard *b)
{
	return  b->count_score(b->get_p1_symbol() ) - b->count_score(b->get_p2_symbol() );
}

vector<OthelloBoard*> MinimaxPlayer::getSuccessors (OthelloBoard *b, char symbol) {
	vector<OthelloBoard*> listOfSuccessors;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ( b->is_legal_move(i, j, symbol)){
				OthelloBoard *temp = new OthelloBoard(*b);
				temp->thisCol = i;				
				temp->thisRow = j;
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
	int compareMin=0, bestRow=0, bestCol=0;

	// if ( b->has_legal_moves_remaining(b->get_p1_symbol()) || b->has_legal_moves_remaining(b->get_p2_symbol()) )
	// 	return utFunc(b);

	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p2_symbol());

	if ( listOfSuccessors.size() == 0 ){
		// free memory
		return utFunc(b);
	}

	// vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p1_symbol() );

	for( int i = 0; i < listOfSuccessors.size(); i++ ){
		compareMin = max(maxU, minValue(listOfSuccessors[i], col, row));
		if ( compareMin > maxU )
		{
			maxU = compareMin;
			bestCol = listOfSuccessors[i]->thisCol;
			bestRow = listOfSuccessors[i]->thisRow;
		}
	}
	col = bestCol;
	row = bestRow;

	return maxU;
}

int MinimaxPlayer::minValue (OthelloBoard *b, int &col, int &row)
{
	int minU = INT_MAX;
	int compareMax=0, bestRow=0, bestCol=0;

	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p2_symbol());

	if ( listOfSuccessors.size() == 0 ){
		// free memory
		return utFunc(b);
	}
	
	for (int i = 0; i < listOfSuccessors.size(); i++){
		compareMax = min(minU, maxValue(listOfSuccessors[i], col, row));
		if ( compareMax < minU )
		{
			minU = compareMax;
			bestCol = listOfSuccessors[i]->thisCol;
			bestRow = listOfSuccessors[i]->thisRow;
		}
	}
	col = bestCol;
	row = bestRow;

	
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
