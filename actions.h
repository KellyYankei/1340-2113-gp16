#include <string>
#include "structures.h"

using namespace std;

#ifndef ACTIONS_H
#define ACTIONS_H

bool checkFormat(string input);
bool makeMatch(string card1, string card2, card pyramid[21], card deck[15], int& pos, card deck_movable[2]);

#endif
