#include <string>
#include <vector>
#include "structures.h"
#include "actions.h"
using namespace std;

#ifndef SAVELOAD_H
#define SAVELOAD_H

bool save(int slot, card pyramid[21], card deck[15], card deck_movable[2], vector<action> steps, int pos, int oppo);
bool load(int slot, card pyramid[21], card deck[15], card deck_movable[2], vector<action>& steps, int& pos, int& oppo);

#endif
