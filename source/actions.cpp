#include <iostream>
#include <string>
#include "actions.h"
#include "structures.h"

using namespace std;

//This function is used to check and return if the user's imput is a valid card. The input is the input by the player. 
//This function only check the grammar. If the suit is invalid, it will be handled in the next function.  
bool checkFormat(string input) {
	if (input.length() == 2 && 'A' <= input[0] <= 'Z' && '0' <= input[1] <= '9')
		return true;
	return false;
}

struct action;

//This function is used to match and remove one or two cards, returns whether the removal is successful. 
//The input of this function includes the 2 cards the player are trying to eliminate (If only one card with num 9 is entered, plug in card2 as empty string), 
//the arrays of cards, the array for the 2 cards displayed below, and the positions of the card displayed below and opportunities remains. 
//The last 3 is used because while the card below is eliminated, these values may need to be changed.
//Input is assumed to be valid, please check validity before implementing function.
//This function will return a struct for recording the operations of the player.
action makeMatch(string card1, string card2, card pyramid[21], card deck[15], int& pos, card deck_movable[2], int& oppo1) {
	char suit1, suit2;
	int num1, num2, i, j;

	//situation 1: one card with num 9
	if (card2 == "") {
		suit1 = card1[0];
		num1 = card1[1] - '0';
		if (num1 != 9)
			return action(0);

		for (i = 0; i < 21; i++) {
			if (pyramid[i].suit == suit1 && pyramid[i].num == 9 && pyramid[i].status == 2) {
				pyramid[i].status = 0;
				int type = 1;
				return action(1,0,type,i);
			}
		}

		for (i = 0; i < 15; i++) {
			if (deck[i].suit == suit1 && deck[i].num == 9 && deck[i].status == 2) {
				if (deck[i] == deck_movable[0]) {
					deck[i].status = 0;
					int type = 4;
					return action(1,1,'l',type,i);
				}
				else if (deck[i] == deck_movable[1]) {
					deck[i].status = 0;				
					pos -= 1;
					if(pos<0) oppo1++;
					int type = 3;
					return action(1,1,'r',type,i);
				}
				else{
					return action(0);
				}
			}
		}
	}

	//situation 2: two cards add up to 9
	else {
		suit1 = card1[0];
		suit2 = card2[0];
		num1 = card1[1] - '0';
		num2 = card2[1] - '0';
		if (num1 + num2 != 9)
			return action(0);

		for (i = 0; i < 21; i++) {
			if (pyramid[i].suit == suit1 && pyramid[i].num == num1 && pyramid[i].status == 2) {
				for (j = 0; j < 21; j++) {
					if (pyramid[j].suit == suit2 && pyramid[j].num == num2 && pyramid[j].status == 2) {
						pyramid[i].status = 0;
						pyramid[j].status = 0;
						bool tmp = 1;	//declare data type of 1 to avoid mismatch
						int type = 2;
						return action(1,0,tmp,type,i,j);
					}
				}

				for (j = 0; j < 15; j++) {
					if (deck[j].suit == suit2 && deck[j].num == num2 && deck[j].status == 2) {
						if (deck[j] == deck_movable[0]) {
							pyramid[i].status = 0;
							deck[j].status = 0;
							int type = 4;
							return action(1,0,1,'l',type,i,j);
						}
							
						else if (deck[j] == deck_movable[1]) {
							pyramid[i].status = 0;
							deck[j].status = 0;
							pos -= 1;
							if(pos<0) oppo1++;
							int type = 4;
							return action(1,0,1,'r',type,i,j);
						}
					}
				}
			}
		}

		for (i = 0; i < 15; i++) {
			if (deck[i].suit == suit1 && deck[i].num == num1 && deck[i].status == 2) {
				for (j = 0; j < 21; j++) {
					if (pyramid[j].suit == suit2 && pyramid[j].num == num2 && pyramid[j].status == 2) {
						if (deck[i] == deck_movable[0]) {
							deck[i].status = 0;
							pyramid[j].status = 0;
							int type = 4;
							return action(1,0,1,'l',type,j,i);
						}
						
						else if (deck[i] == deck_movable[1]) {
							deck[i].status = 0;
							pyramid[j].status = 0;
							pos -= 1;
							if(pos<0) oppo1++;
							int type = 4;
							return action(1,0,1,'r',type,j,i);
						}
					}
				}

				for (j = 0; j < 15; j++) {
					if (deck[j].suit == suit2 && deck[j].num == num2 && deck[j].status == 2) {
						deck[i].status = 0;
						deck[j].status = 0;
						pos -= 1;
						if(pos<0) oppo1++;
						bool tmp = 0;
						int type = 5;
						return action(1,0,tmp,type,i,j);
					}
				}
			}
		}
	}

	return action(0);    //If all judgment statements are false, then the program will eventually decide that the operation is not reasonable
}

//This function is used to set the board to initial state (for restarting same game). The input are the arrays for the cards and the position of the card
//displayed below. This function set these to the initial status. This function do not return anything.
void reset(card pyramid[21], card deck[15], int& pos, int &oppo) {
	int i;

	for (i = 0; i < 21; i++) 
		pyramid[i].status = 1;
	
	for (i = 0; i < 15; i++)
		deck[i].status = 1;

	pos = 0;
	oppo = 2;
}
