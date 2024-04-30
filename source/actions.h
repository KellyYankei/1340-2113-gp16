#include <string>
#include "structures.h"

using namespace std;

#ifndef ACTIONS_H
#define ACTIONS_H

struct action{
	bool success;
	bool card1;
	bool card2;
	char pos1;
	char pos2;
    int type;   //record the type so more convenient to reverse
    int index1, index2;
	/*
	0: card is found in pyramid
	1: card is found in deck
	pos reflect the position of card in deck
	l: left
	r: right
	using char to build constructor
	*/
	action(bool parameter1){
		success = parameter1;
	}	//unsuccessful
	action(bool parameter1,bool parameter2,int tp,int id1){
		success = parameter1;
		card1 = parameter2;
        type = tp;
        index1 = id1;
	}	//9 in pyramid, type = 1
	action(bool parameter1,bool parameter2,bool parameter3,int tp,int id1,int id2){
		success = parameter1;
		card1 = parameter2;
		card2 = parameter3;
        type = tp;
        index1 = id1;
		index2 = id2;
	}	//two cards in pyramid, type = 2
	action(bool parameter1,bool parameter2,char position1,int tp,int id1){
		success = parameter1;
		card1 = parameter2;
		pos1 = position1;
        type = tp;
        index1  = id1;
	}	//9 in deck, type = 3
	action(bool parameter1,bool parameter2,bool parameter3,char position1,int tp,int id1,int id2){
		success = parameter1;
		card1 = parameter2;
		card2 = parameter3;
		pos2 = position1;
        type = tp;
        index1 = id1;
		index2 = id2;
	}	//one in pyramid & one in deck, the one in pyramid always first, type = 4
	// conbine two cards in deck, type = 5
	// flip, type = 6
};
bool checkFormat(string input);
action makeMatch(string card1, string card2, card pyramid[21], card deck[15], int& pos, card deck_movable[2], int &oppo1);
void reset(card pyramid[21], card deck[15], int& pos, int &oppo);

#endif
