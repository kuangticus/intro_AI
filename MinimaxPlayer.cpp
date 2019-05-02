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

using namespace std;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

// this function will be used to return the utility value of the next move
// if max player will return the value with the max utility
// if min player then will return the lowest utility value
int MinimaxPlayer::utility(OthelloBoard *theboard )
{

	// if ( theboard->count_score(theboard->get_p2_symbol()) > theboard->count_score(theboard->get_p2_symbol()) )
	// 	return 1;

	// else if ( theboard->count_score(theboard->get_p2_symbol()) == theboard->count_score(theboard->get_p2_symbol()) )
	// 	return 0;

	// else
	// 	return -1;

	return theboard->count_score(theboard->get_p2_symbol()) - theboard->count_score(theboard->get_p2_symbol());
}

// this function will generate the list of all possible successor from the given state of one move
// away from the next state where the new numbers are used
vector<OthelloBoard *> MinimaxPlayer::successorsGenerate(OthelloBoard *theboard, vector<int*> *actions)
{
	// gathering the th
	vector<OthelloBoard*> moves;
	
	for (int i=0; i < 4 ; i++ )
	{
		for ( int j = 0 ; j < 4 ; j++ )
		{
			// using the in house function to check which moves are legal for the current state
			if ( theboard->is_legal_move(i, j, theboard->get_p2_symbol()) )
			{
				int *num = new int(2);
				num[0] = i;
				num[1] = j;
				cout << "states generated: " << i << " and "<< j << endl;
				actions->push_back(num);
				OthelloBoard *temp = new OthelloBoard(*theboard);
				temp->play_move(i, j, theboard->get_p2_symbol());
				moves.push_back(temp);
			}
		}
	}
	return moves;
}

int MinimaxPlayer::maxVal(OthelloBoard *theboard)
{
	int maxUtility = -100;
	vector <int*> nums;
	if(isTerminal(theboard))
	{
		cout << " never terminals? : " << utility(theboard) << endl;
		return utility(theboard);
	}

	vector<OthelloBoard*> states = successorsGenerate(theboard, &nums);

	for ( int i =0; i< states.size(); i++)
	{
		int temp = minVal(states[i]);
		cout << "this is min value from maxVal " << temp << endl;
		maxUtility = max(maxUtility, minVal(states[i]));
	}
	for ( int i =0; i< states.size(); i++)
	{
		delete states[i];
		delete nums[i];
	}

	return maxUtility;
}

int MinimaxPlayer::minVal(OthelloBoard *theboard)
{
	int minUtility = 100;
	vector<int*> nums;
	if(isTerminal(theboard))
	{
		return utility(theboard);
	}
	
	vector<OthelloBoard*> states = successorsGenerate(theboard, &nums);


	for ( int i =0; i< states.size(); i++)
	{
		minUtility = min(minUtility, maxVal(states[i]));		
	}
	for ( int i =0; i< states.size(); i++)
	{
		delete states[i];
		delete nums[i];
	}
	return minUtility;
}	
void MinimaxPlayer::get_move(OthelloBoard* b, int &col, int &row)
{
	vector<int*> list;	
	vector<OthelloBoard*> possibleMoves = successorsGenerate(b, &list);
	int utVal =  maxVal(b);
	cout << "value of utVal: " <<utVal << endl;

	cout << "size of list: " << list.size() << endl;	

	col = list[utVal][0];
	row = list[utVal][1];

	cout << "moves list: " << col << " and " << row << endl;

	for ( int i=0; i < list.size(); i++)
		delete list[i];
}

bool MinimaxPlayer::isTerminal(OthelloBoard *theboard){
	if ( theboard->has_legal_moves_remaining(theboard->get_p1_symbol()) || theboard->has_legal_moves_remaining(theboard->get_p2_symbol()) )
		return false;
	else 
		return true;
}	

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
