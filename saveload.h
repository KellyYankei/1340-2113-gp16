#include <string>
#include <vector>
#include "structures.h"
using namespace std;

#ifndef SAVELOAD_H
#define SAVELOAD_H

void save(int slot, card pyramid[21], card deck[15], vector<action> steps);
void load(int slot, card pyramid[21], card deck[15], vector<action>& steps);

#endif
