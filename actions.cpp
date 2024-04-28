#include <iostream>
#include <string>
#include "actions.h"
#include "structures.h"

using namespace std;

//Check and return if the entered card is valid
bool checkFormat(string input) {
	if (input.length() == 2 && 'A' <= input[0] <= 'Z' && '0' <= input[1] <= '9')
		return true;
	return false;
}

struct action;

//Match and remove one or two cards, returns whether removal is successful. Input is assumed to be valid, please check validity before implementing function.
//(If only one card with num 9 is entered, plug in card2 as empty string)
action makeMatch(string card1, string card2, card pyramid[21], card deck[15], int& pos, card deck_movable[2]) {
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
					int type = 3;
					return action(1,1,'r',type,i);
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
						bool tmp = 0;
						int type = 5;
						return action(1,0,tmp,type,i,j);
					}
				}
			}
		}
	}

	return false;
}

//set the board to initial state (for restarting same game)
void reset(card pyramid[21], card deck[15], int& pos) {
	int i;

	for (i = 0; i < 21; i++) 
		pyramid[i].status = 1;
	
	for (i = 0; i < 15; i++)
		deck[i].status = 1;

	pos = 0;
}
