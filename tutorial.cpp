#include <iostream>
#include <string>
#include <time.h>
#include "judgement.h"
#include "printing.h"
#include "structures.h"
#include "tutorial.h"

using namespace std;

#define BLUE	"\033[34m"
#define CLSCR	"\033c"
#define RESET	"\033[0m"

//for waiting t seconds before further execution
void delay(int t) {
	clock_t start = clock();
	clock_t period = (clock_t)t * CLOCKS_PER_SEC;
	while ((clock() - start) < period);
}

//for printing tutorial instructions
//reads instruction as a string and output it in blue in a speech bubble
void printInstruction(string instruction) {
	int l = instruction.length(), i;

	cout << BLUE << "╭";
	for (i = 0; i < l; i++)
		cout << "─";
	cout << "╮" << endl << "│" << instruction << "│" << endl << "╰";
	for (i = 0; i < l; i++)
		cout << "─";
	cout << "╯" << endl << RESET;
}

//print in blue instruction for useful commands (P, N, Q), can control whether to print P or N
void printCommands(bool p1, bool p2, bool p3) {
	string commands[4] = { "\"P\"revious instruction", "\"N\"ext instruction", "\"F\"lip card", "\"Q\"uit tutorial"};
	cout << BLUE << "Useful commands (enter quoted letter)" << endl;

	if (p1)
		cout << commands[0] << ", ";

	if (p2)
		cout << commands[1] << ", ";

	if (p3)
		cout << commands[2] << ", ";

	cout << commands[3] << endl << RESET;
}

//run the entire tutorial
void tutorial() {
	//setting up the tutorial game
	int i;
	card tutPyramid[21], tutDeck[15];
	string tutCards[36] = {
		"C9",
		"S5", "D4",
		"D2", "H1", "C1",
		"S2", "C3", "S3", "C4",
		"C8", "C6", "S9", "H2", "S1",
		"S6", "H5", "C8", "D1", "S7", "C5",
		"D3", "H6", "D5", "H8", "C2", "D5", "A1", "A1", "A1", "A1", "A1", "A1", "A1", "A1", "A1" };

	for (i = 0; i < 21; i++) {
		tutPyramid[i].suit = tutCards[i][0];
		tutPyramid[i].num = tutCards[i][1] - '0';
		tutPyramid[i].status = 1;
	}

	for (i = 0; i < 15; i++) {
		tutDeck[i].suit = tutCards[i + 21][0];
		tutDeck[i].num = tutCards[i + 21][1] - '0';
		tutDeck[i].status = 1;
	}

	//instructions for the tutorial
	//0. basic rule
	string instructions0[] = {
		"You will learn to play a simplified version of the game Pyramid.",
		"This is a game where you match and remove cards with numbers adding up to 9.",
	};

	//1. introduce pyramid
	string instructions1[] = {
		"This is the PYRAMID, with 21 cards.",
		"Each card face consists of a letter and a number from 1 to 9.",
		"The letters are C, D, S and H, representing the four suits -",
		"C(lubs), D(iamonds), S(pades), and H(earts).",
		"Each suit is represented by its initial letter (e.g. \"S\" for Spades).",
		"You can only remove a card that is not obstructed by other cards below it.",
		"For the initial case, this means only cards in the bottom row can be removed.",
		"These removeable cards are displayed in green.",
		"Now, you should be able to find a pair that add up to 9.",
		"Please enter their faces (suit + number), separated by a space."
	};

	//2. fail in 1
	string instructions2a[] = {
		"Perhaps you misheard the requirement? Let me repeat.",
		"You need to find to cards in green whose numbers add up to 9.",
		"Please enter their faces (suit + number), separated by a space."
	};

	//3. succeed in 1, introduce special case
	string instructions2b[] = {
		"Great!",
		"You can see that the card S9 is now uncovered.",
		"Since its number is already 9, it can be removed without matching.",
		"Simply enter its face now to remove it."
	};

	//4. fail in 3
	string instructions3a[] = {
		"Perhaps the instruction was unclear? Let me repeat.",
		"S9 already has number 9, so you can remove it without matching.",
		"Simply enter its face now to remove it."
	};

	//5. succeed in 3, foreshadow
	string instructions3b[] = {
		"You are doing very well!",
		"But oops, looks like we don\'t have any more matches...",
		"Never mind, the new feature is here to save you -",
	};

	//6. introduce deck
	string instructions4[] = {
		"The DECK.",
		"It provides you with extra options for matching.",
		"And guess what? We have a match right there!",
		"Enter the matching pair, separated by a space."
	};

	//7. fail in 6 
	string instructions5a[] = {
		"Come on. You can do this. Just match two cards adding up to 9.",
		"Enter the matching pair, separated by a space."
	};

	//8. succeed in 6, introduce flip
	string instructions5b[] = {
		"Very good!",
		"To find more matches from the deck, you have to flip through it.",
		"Every time you flip, the top card in the left pile is moved to the right.",
		"For flipping, simply enter \"F\"."
	};

	//9. fail in 8
	string instructions6a[] = {
		"Not getting the hang of it? Let's make it brief: ",
		"You need to flip through the deck for more cards to match.",
		"For flipping, simply enter \"F\"."
	};

	//10. succeed in 8 or 10 (first time) or 11 (first time), more flips
	string instructions6b[] = {
		"That's it!",
		"Now flip some more!",
		"Enter \"F\" to flip."
	};

	//11. fail in 10
	string instructions7a[] = {
		"Apparently there are no matches now. You should flip some more.",
		"Enter \"F\" to flip."
	};

	//12. succeed in 10 (second time), found match
	string instructions7b[] = {
		"Here's a match!",
		"Enter the matching pair."
	};

	//13. fail in 12
	string instructions8a[] = {
		"That doesn't look like a match.",
		"Enter the matching pair."
	};

	//14. succeed in 12, continue into 15
	string instructions8b[] = {
		"Alright. You are prepared.",
		"Now let's fast forward to the end of this one game."
	};

	//15. further explanation of deck
	string instructions9[] = {
		"Somehow you've used up all the cards available in the deck.",
		"That's right. The deck is not endless.",
		"It only contains those cards that aren't in the pyramid.",
		"However, the game is still solvable. Give it a go.",
		"Enter your command."
	};

	//16. fail in 15
	string instructions10a[] = {
		"Remember - match 9.",
		"Enter your command."
	};

	//17. succeed in 15, last move
	string instructions10b[] = {
		"Almost there!",
		"Enter your command."
	};

	//18. fail in 17
	string instructions11a[] = {
		"Have patience. You're getting very close!",
		"Enter your command."
	};

	//19. succeed in 17, end of tutorial
	string instructions11b[] = {
		"Congratulations!",
		"Now you have got the gist of the game.",
		"Have fun!"
	};

	//displaying the instructions
	int idx[2] = { 0, 0 }, pos = 0, oppo = 1;
	string input = "";
	card deck_movable[2] = { tutDeck[0] };
	deck_movable[1].suit = 'A';
	deck_movable[1].num = 1;
	deck_movable[1].status = 0;

	while (true) {
		set_status(tutPyramid);

		if (input == "Q")
			return;

		cout << CLSCR;

		if (idx[0] == 0) {
			printInstruction(instructions0[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N")
				idx[1] += 1;
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			//jump to 1
			if (idx[1] == size(instructions0)) {
				idx[0] = 1;
				idx[1] = 0;
			}
		}

		else if (idx[0] == 1) {
			printmap(tutPyramid);
			printInstruction(instructions1[idx[1]]);
			if (idx[1] == size(instructions1) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P")
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions1) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions1) - 1) {
				if (input == "C8 D1" || input == "D1 C8") {
					idx[0] = 3; //jump to 2b
					tutPyramid[17].status = 0;
					tutPyramid[18].status = 0;
				}
				else
					idx[0] = 2; //jump to 2a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			//jump to 0
			if (idx[1] == -1) {
				idx[0] = 0;
				idx[1] = size(instructions0) - 1;
			}
		}

		else if (idx[0] == 2) {
			printmap(tutPyramid);
			printInstruction(instructions2a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions2a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions2a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions2a) - 1) {
				if (input == "C8 D1" || input == "D1 C8") {
					idx[0] = 3;//jump to 2b
					tutPyramid[17].status = 0;
					tutPyramid[18].status = 0;
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 3) {
			printmap(tutPyramid);
			printInstruction(instructions2b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions2b) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions2b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions2b) - 1) {
				if (input == "S9") {
					idx[0] = 5;//jump to 3b
					tutPyramid[12].status = 0;
				}
				else
					idx[0] = 4;//jump to 3a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 4) {
			printmap(tutPyramid);
			printInstruction(instructions3a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions3a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions3a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions3a) - 1) {
				if (input == "S9") {
					idx[0] = 5;//jump to 3b
					tutPyramid[12].status = 0;
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 5) {
			printmap(tutPyramid);
			printInstruction(instructions3b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N")
				idx[1] += 1;
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			//jump to 4
			if (idx[1] == size(instructions3b)) {
				idx[0] = 6;
				idx[1] = 0;
			}
		}

		else if (idx[0] == 6) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions4[idx[1]]);
			if (idx[1] == size(instructions4) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P")
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions4) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions4) - 1) {
				if (input == "D3 S6" || input == "S6 D3") {
					idx[0] = 8;//jump to 5b
					tutPyramid[15].status = 0;
					tutDeck[0].status = 0;
					deck_movable[0] = tutDeck[1];
				}
				else
					idx[0] = 7;//jump to 5a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			if (idx[1] == -1) {
				idx[0] = 5;//jump to 3b
				idx[1] = size(instructions3b) - 1;
			}
		}

		else if (idx[0] == 7) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions5a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions5a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions5a) -1)
				idx[1] += 1;
			else if (idx[1] == size(instructions5a) - 1) {
				if (input == "D3 S6" || input == "S6 D3") {
					idx[0] = 8;//jump to 5b
					tutPyramid[15].status = 0;
					tutDeck[0].status = 0;
					deck_movable[0] = tutDeck[1];
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 8) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions5b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions5b) - 1)
				printCommands(1, 0, 1);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions5b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions5b) - 1) {
				if (input == "F") {
					idx[0] = 10;//jump to 6b
					pos += 1;
					deck_movable[1] = deck_movable[0];
					deck_movable[0] = tutDeck[2];
				}
				else
					idx[0] = 9;//jump to 6a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 9) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions6a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions6a) - 1)
				printCommands(1, 0, 1);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions6a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions6a) - 1) {
				if (input == "F") {
					idx[0] = 10;//jump to 6b
					pos += 1;
					deck_movable[1] = deck_movable[0];
					deck_movable[0] = tutDeck[2];
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 10) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions6b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions6b) - 1)
				printCommands(1, 0, 1);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions6b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions6b) - 1) {
				if (input == "F") {
					pos += 1;
					deck_movable[1] = deck_movable[0];
					if (pos == 2)//remain at 6b
						deck_movable[0] = tutDeck[3];
					else if (pos == 3) {
						idx[0] = 12;//jump to 7b
						deck_movable[0] = tutDeck[4];
					}
				}
				else
					idx[0] = 11;//jump to 7a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 11) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions7a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions7a) - 1)
				printCommands(1, 0, 1);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions7a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions7a) - 1) {
				if (input == "F") {
					pos += 1;
					deck_movable[1] = deck_movable[0];
					if (pos == 2) {
						idx[0] = 10;//jump to 6b
						deck_movable[0] = tutDeck[3];
					}
					else if (pos == 3) {
						idx[0] = 12;//jump to 7b
						deck_movable[0] = tutDeck[4];
					}
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 12) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions7b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions7b) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions7b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions7b) - 1) {
				if (input == "C2 S7" || input == "S7 C2") {
					idx[0] = 14;//jump to 8b
					tutPyramid[19].status = 0;
					tutDeck[4].status = 0;
					deck_movable[0] = tutDeck[5];
				}
				else
					idx[0] = 13;//jump to 8a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 13) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions8a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions8a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions7b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions7b) - 1) {
				if (input == "C2 S7" || input == "S7 C2") {
					idx[0] = 14;//jump to 8b
					tutPyramid[19].status = 0;
					tutDeck[4].status = 0;
					deck_movable[0] = tutDeck[5];
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 14) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions8b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N")
				idx[1] += 1;
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			//jump to 9
			if (idx[1] == size(instructions8b)) {
				idx[0] = 15;
				idx[1] = 0;
				for (i = 3; i < 21; i++)
					tutPyramid[i].status = 0;
				for (i = 0; i < 15; i++)
					tutDeck[i].status = 0;
			}
		}

		else if (idx[0] == 15) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions9[idx[1]]);
			if (idx[1] == size(instructions9) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P")
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions9) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions9) - 1) {
				if (input == "S5 D4" || input == "D4 S5") {
					idx[0] = 17;//jump to 10b
					tutPyramid[1].status = 0;
					tutPyramid[2].status = 0;
				}
				else
					idx[0] = 16;//jump to 10a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			//jump to 8b
			if (idx[1] == -1) {
				idx[0] = 14;
				idx[1] = size(instructions8b) - 1;
				for (i = 3; i < 21; i++)
					tutPyramid[i].status = 1;
				tutPyramid[12].status = 0;
				tutPyramid[15].status = 0;
				tutPyramid[17].status = 0;
				tutPyramid[18].status = 0;
				tutPyramid[19].status = 0;
				set_status(tutPyramid);
				for (i = 0; i < 15; i++)
					tutDeck[i].status = 1;
				tutDeck[0].status = 0;
				tutDeck[4].status = 0;
			}
		}

		else if (idx[0] == 16) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions10a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions10a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions10a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions10a) - 1) {
				if (input == "S5 D4" || input == "D4 S5") {
					idx[0] = 17;
					tutPyramid[1].status = 0;
					tutPyramid[2].status = 0;
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 17) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions10b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions10b) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions10b) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions10b) - 1) {
				if (input == "C9") {
					idx[0] = 19;//jump to 11b
					tutPyramid[0].status = 0;
				}
				else
					idx[0] = 18;//jump to 11a
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 18) {
			printmap(tutPyramid);
			print_deck(pos, tutDeck, oppo, deck_movable);
			printInstruction(instructions11a[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else if (idx[1] == size(instructions11a) - 1)
				printCommands(1, 0, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N" && idx[1] != size(instructions11a) - 1)
				idx[1] += 1;
			else if (idx[1] == size(instructions11a) - 1) {
				if (input == "C9") {
					idx[0] = 19;//jump to 11b
					tutPyramid[0].status = 0;
				}
				idx[1] = 0;
			}
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}
		}

		else if (idx[0] == 19) {
			printInstruction(instructions11b[idx[1]]);
			if (idx[1] == 0)
				printCommands(0, 1, 0);
			else
				printCommands(1, 1, 0);
			cout << endl << "Enter command: ";

			getline(cin, input);
			if (input == "P" && idx[1] != 0)
				idx[1] -= 1;
			else if (input == "N")
				idx[1] += 1;
			else if (input != "Q") {
				cout << "Invalid input";
				delay(1);
			}

			if (idx[1] == size(instructions11b))
				return;//end of tutorial
		}
	}
}
