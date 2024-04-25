#ifndef STRUCTURES_H
#define STRUCTURES_H

/*
status:
0: removed
1: unremoved, unremovable
2: unremoved, removable
*/
struct card {
	char suit;
	int num;
	int status;
};

bool operator==(const card& card1, const card& card2) {
	return (card1.suit == card2.suit && card1.num == card2.num && card1.status == card2.status);
}

#endif