#include "structures.h"

#ifndef PRINTING_H
#define PRINTING_H

void printspace(int i);
void printcard_up(int status);
void printcard_mid(int status, char suit, int num);
void printcard_bottom(int status);
void printmap(card map[]);
void Initializing(card Cards[], card pyramid[], card deck[]);
int searchpyramid(card pyramid[], char s, int n);
int searchshow(card show[], char s, int n);
int print_deck(int &pos1, card deck[], int &oppo1, card show[2]);

#endif
