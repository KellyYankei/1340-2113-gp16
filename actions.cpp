#include <iostream>
#include <string>
#include "structures.h"

using namespace std;

//Check and return if the entered card is valid
bool checkFormat(string input) {
	if (input.length() == 2 && 'A' <= input[0] <= 'Z' && '0' <= input[1] <= '9')
		return true;
	return false;
}

//Match and remove one or two cards, returns whether removal is successful. Input is assumed to be valid, please check validity before implementing function.
//(If only one card with num 9 is entered, plug in card2 as empty string)
bool makeMatch(string card1, string card2, card pyramid[21], card deck[15], int& pos, card deck_movable[2]) {
	char suit1, suit2;
	int num1, num2, i, j;

	//situation 1: one card with num 9
	if (card2 == "") {
		suit1 = card1[0];
		num1 = card1[1];
		if (num1 != 9)
			return false;

		for (i = 0; i < 21; i++) {
			if (pyramid[i].suit == suit1 && pyramid[i].num == 9 && pyramid[i].status == 2) {
				pyramid[i].status = 0;
				return true;
			}
		}

		for (i = 0; i < 15; i++) {
			if (deck[i].suit == suit1 && deck[i].num == 9 && deck[i].status == 1) {
				if (deck[i] == deck_movable[0]) {
					deck[i].status = 0;
					return true;
				}
				else if (deck[i] == deck_movable[1]) {
					deck[i].status = 0;
					pos -= 1;
					return true;
				}
			}
		}
	}

	//situation 2: two cards add up to 9
	else {
		suit1 = card1[0];
		suit2 = card2[0];
		num1 = card1[1];
		num2 = card2[1];
		if (num1 + num2 != 9)
			return false;

		for (i = 0; i < 21; i++) {
			if (pyramid[i].suit == suit1 && pyramid[i].num == num1 && pyramid[i].status == 2) {
				for (j = 0; j < 21; j++) {
					if (pyramid[j].suit == suit2 && pyramid[j].num == num2 && pyramid[j].status == 2) {
						pyramid[i].status = 0;
						pyramid[j].status = 0;
						return true;
					}
				}

				for (j = 0; j < 15; j++) {
					if (deck[j].suit == suit2 && deck[j].num == num2 && deck[j].status == 1) {
						if (deck[j] == deck_movable[0]) {
							pyramid[i].status = 0;
							deck[j].status = 0;
							return true;
						}

						else if (deck[j] == deck_movable[1]) {
							pyramid[i].status = 0;
							deck[j].status = 0;
							pos -= 1;
							return true;
						}
					}
				}
			}
		}

		for (i = 0; i < 15; i++) {
			if (deck[i].suit == suit1 && deck[i].num == num1 && deck[i].status == 1) {
				for (j = 0; j < 21; j++) {
					if (pyramid[j].suit == suit2 && pyramid[j].num == num2 && pyramid[j].status == 2) {
						if (deck[i] == deck_movable[0]) {
							deck[i].status = 0;
							pyramid[j].status = 0;
							return true;
						}
						
						else if (deck[i] == deck_movable[1]) {
							deck[i].status = 0;
							pyramid[j].status = 0;
							pos -= 1;
							return true;
						}
					}
				}

				for (j = 0; j < 15; j++) {
					if (deck[j].suit == suit2 && deck[j].num == num2 && deck[j].status == 1) {
						deck[i].status = 0;
						deck[j].status = 0;
						pos -= 1;
						return true;
					}
				}
			}
		}
	}

	return false;
}