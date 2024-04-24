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

#endif