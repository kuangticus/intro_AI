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
// Para: the othelloboard state and char  
// Description: gets the successors of the the symbol that is passed in 
vector<OthelloBoard*> MinimaxPlayer::getSuccessors (OthelloBoard *b, char symbol) {
	vector<OthelloBoard*> listOfSuccessors; // this is the listOfSuccessors

	OthelloBoard *temp;
	for (int i = 0; i < 4; i++)	// 4 x 4 for loop will generate all of the things that 
	{
		for (int j = 0; j < 4; j++) 
		{
			// using the the legal move to get the best move and push them into the the vector
			int n = b->is_legal_move(i, j, symbol);
			switch(n)
			{
				// creating a new temp of the othelloboard for the new set
				case 1:
					temp = new OthelloBoard(*b);
					temp->mutateThisCol(i);	// this will be the mutator that sets the action state of the col		
					temp->mutateThisRow(j); // this will be the mutator that sets the action state of the row
					temp->play_move(i,j, symbol);	// this play the valid move that is generated
					listOfSuccessors.push_back(temp);	// pushes the thing into the listOfSuccessors
					break;

				default: // this will break out if there isnt a case that is true
					break;
			}
		}
	}
	return listOfSuccessors;
}

// Function: maxValue
// Para: the othelloboard , col, row 
// Description:  this is the max value section of the minimax algo
int MinimaxPlayer::maxValue (OthelloBoard *b, int &col, int &row)
{
	int maxU = INT_MIN, compareMin = 0;   // this will be the minValue for the comparison and the MaxU
	int bestSol[2];		// this will be the best soltion action path

	// getting the successors for thet the p1_symbol()
	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p1_symbol());

	// this will check the to see if there aren't anymore the 
	if ( listOfSuccessors.size() == 0 ) { return utFunc(b); } // this wiill return the utility value at the terminal by subtracting 

	// this is used to loop through the list of successors that have been generated from the before
	for( int i = 0; i < listOfSuccessors.size(); i++ ){
		// for compar min will get the maximized value form the minValue function
		compareMin = max(maxU, minValue(listOfSuccessors[i], col, row));
		// if the compareMin is greater than the the MaxU

		// will use this to check generated is lessgreater than the maxU for best more calculation
		switch(compareMin > maxU) // checks which case it is for the switch
		{
		case 1:
			maxU = compareMin; // the maxU will get updated
			bestSol[0] = listOfSuccessors[i]->getThisCol(); // the bestSol col (0) will get updated with the action col
			bestSol[1] = listOfSuccessors[i]->getThisRow();	// the bestSol row (1) will get the update action sol row
			break;
		default: // if there isnt a match then it will break out and continue without changing anything.
			break;
		}
	}
	// this is the updated best action to take for the maximizing player
	col = bestSol[0];
	row = bestSol[1];

	// freeing the memory here so that there will won't be mem leak
	for (int i = 0; i < listOfSuccessors.size(); i++ )
	{
		delete listOfSuccessors[i]; // delete the the list of successor freeing mem
	}
	return maxU;
}

// Function: minValue
// Para: the othelloboard state, col and row 
// Description: this is the minValue that is a for the minimizing player
int MinimaxPlayer::minValue (OthelloBoard *b, int &col, int &row)
{
	int minU = INT_MAX, compareMax = 0; // the comparison value that are used to compare
	int bestSol[2]; // used to get the best solution action steps

	// gets the list of successor from the p2 symbols
	vector<OthelloBoard*> listOfSuccessors = getSuccessors(b, b->get_p2_symbol());

	// the will be the terminal test to simply checks to see if there aren't any 
	if ( listOfSuccessors.size() == 0 ) { return utFunc(b); } 

	// going through the list of successor the from the generate 
	for (int i = 0; i < listOfSuccessors.size(); i++){
		// this will get the compareMax getting the min from the maxValue 
		compareMax = min(minU, maxValue(listOfSuccessors[i], col, row));
		// the compare the the minU and will switch through case statements
		switch(compareMax < minU){
			case 1:
				minU = compareMax;	// the compareMax the ill get put into the minU
				bestSol[0] = listOfSuccessors[i]->getThisCol(); // the bestSol col will get the action col from the board
				bestSol[1] = listOfSuccessors[i]->getThisRow(); // the bestSol row will get the action row from the board
				break;

			default: // default will break if there isn't anything that is true
				break;
		}
	}
	col = bestSol[0]; // the col this is the best col that was from the bestSol col
	row = bestSol[1]; // the row this is the best row the was from the bestSol row

	// this is what I use to clear and free the memory of the listOfSuccessors
	for (int i = 0; i < listOfSuccessors.size(); i++ )
	{
		// deleteing the new
		delete listOfSuccessors[i];
	}
	return minU;
}

// Function: get_move
// Para: othelloboard, col, row
// Description: this function will call the minvalue or maxvalue depending on the p1 symbol 
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row)
{
	int bestMove; // this is dummy variable
	switch( symbol == b->get_p1_symbol() )
	{
		case 0:
			// this is calling the minValue for is p1 is X 
			bestMove = minValue(b, col, row);
			break;

		case 1:
			// this is calling the maxValue is p2 is O
			bestMove = maxValue(b, col, row);
			break;

		default: // breaks this and if this doesn't work 
			break;

	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
