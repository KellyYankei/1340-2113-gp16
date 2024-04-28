#include <iostream>
#include <string>
#include "printing.h"
#include "structures.h"

using namespace std;

#define BLUE	"\033[34m"
#define CLSCR	"\033c"
#define RESET	"\033[0m"

//for printing tutorial instructions
//reads instruction as a string and output it in blue in a speech bubble
void printInstruction(string instruction) {
	int l = instruction.length(), i;

	cout << BLUE << '╭';
	for (i = 0; i < l; i++)
		cout << "─";
	cout << '╮' << endl << '│' << instruction << '│' << endl << '╰';
	for (i = 0; i < l; i++)
		cout << "─";
	cout << '╯' << endl << RESET;
}

//run the entire tutorial
//CDSH
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
		"D3", "H6", "D5", "H8", "C2", "D5", "A0", "A0", "A0", "A0", "A0", "A0", "A0", "A0", "A0"};

	for (i = 0; i < 21; i++) {
		tutPyramid[i].suit = tutCards[i][0];
		tutPyramid[i].num = tutCards[i][1];
		tutPyramid[i].status = 1;
	}

	for (i = 0; i < 15; i++) {
		tutDeck[i].suit = tutCards[i + 21][0];
		tutDeck[i].num = tutCards[i + 21][1];
		tutDeck[i].status = 1;
	}

	//instructions for the tutorial
	string instructions0[] = {
		"You will learn to play a simplified version of the game Pyramid.",
		"This is a game where you match and remove cards with numbers adding up to 9.",
	};

	string instructions1[] = {
		"This is the PYRAMID, with 21 cards",
		"Each card face consists of a letter and a number from 1 to 9.",
		"The letters are C, D, S and H, representing the four suits -",
		"S(pades), D(iamonds), C(lubs), and H(earts).",
		"Each suit is represented by its initial letter (e.g. \"S\" for Spades).",
		"You can only remove a card that is not obstructed by other cards below it.",
		"For the initial case, this means only cards in the bottom row can be removed.",
		"These removeable cards are displayed in green.",
		"Now, you should be able to find a pair that add up to 9.",
		"Please enter their faces (suit + number), separated by a space."
	};

	string instructions2a[] = {
		"Perhaps you misheard the requirement? Let me repeat.",
		"You need to find to cards in green whose numbers add up to 9.",
		"Please enter their faces (suit + number), separated by a space."
	};

	string instructions2b[] = {
		"Great!",
		"You can see that the card S9 is now uncovered.",
		"Since its number is already 9, it can be removed without matching.",
		"Simply enter its face to remove it."
	};

	string instructions3a[] = {
		"Perhaps the instruction was unclear? Let me repeat.",
		"S9 already has number 9, so you can remove it without matching."
		"Simply enter its face to remove it."
	};
	
	string instructions3b[] = {
		"You are doing very well!",
		"But oops, looks like we don\'t have any more matches..."
		"Never mind, the new feature is here to save you -",
	};

	string instructions4[] = {
		"The DECK."
		"It provides you with extra options for matching."
		"And guess what? We have a match right there!"
		"Enter the matching pair, separated by a space."
	};

	string instructions5a[] = {
		"Come on. You can do this. Just match two cards adding up to 9.",
		"Enter the matching pair, separated by a space."
	};

	string instructions5b[] = {
		"Very good!",
		"To find more matches from the deck, you have to flip through it.",
		"Every time you flip, the top card in the left pile is moved to the right.",
		"For flipping, simply enter \"F\"."
	};

	string instructions6a[] = {
		"Not getting the hang of it? Let's make it one sentence: ",
		"Enter \"F\" to flip through the deck for more cards to match. Now try.",
		"For flipping, simply enter \"F\"."
	};

	string instructions6b[] = {
		"That's it!",
		"Now flip some more!",
		"Enter \"F\" to flip."
	};

	string instructions7a[] = {
		"Apparently there are no matches now. You should flip some more.",
		"Enter \"F\" to flip."
	};

	string instructions7b[] = {
		"Here's a match!",
		"Enter the matching pair."
	};

	string instructions8a[] = {
		"That doesn't look like a match.",
		"Enter the matching pair."
	};

	string instructions8b[] = {
		"Alright. You are prepared.",
		"Now let's fast forward to the end of this one game."
	};

	string instructions9[] = {
		"Somehow you've used up all the cards available in the deck.",
		"That's right. The deck is not endless.",
		"It only contains those cards that aren't in the pyramid.",
		"However, the game is still solvable. Give it a go.",
		"Enter your command."
	};

	string instructions10a[] = {
		"Remember - match 9.",
		"Enter your command."
	};

	string instructions10b[] = {
		"Getting close!",
		"Enter your command."
	};

	string instructions11[] = {
		"Now you have got the gist of the game.",
		"Have fun!"
	};
}