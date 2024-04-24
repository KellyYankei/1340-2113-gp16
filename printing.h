#include "structures.h"

#ifndef PRINTING_H
#define PRINTING_H
void printspace(int i);
void printcard_up(int status);
void printcard_mid(int status, char suit, int num);
void printcard_bottom(int status);
void printmap(card map[]);
void shuffle(card deck[], int len);
void Initialzing(card deck[]);
void searchpyramid(card pyramid[], char s, int n);
#endif